// UNN, IITMM, Course "Algorithms and Data Structures"
// 
// Noskov I.A.

#pragma once
#include <list>
#include <utility>
#include <algorithm> 
#include <vector>
#include <ostream>
#include <string>
#include <iostream>


namespace maps {
	template<class T>
	class TableInterface {
	public:
		virtual bool insert(std::size_t key, const T& data) = 0;
		virtual bool erase(std::size_t key) = 0;
		virtual std::pair<std::size_t, T>* find(std::size_t key) = 0;
		virtual std::size_t get_size() const = 0;
		virtual bool is_empty() = 0;
		virtual void clear() = 0;
	};


	template<class T, class CellType = std::pair<std::size_t, T>>
	class TableByArray : public TableInterface<T> {
	protected:
		std::vector<CellType> data;
		std::size_t sz;
	public:
		std::size_t get_size() const {
			return sz;
		};
		void clear() {
			sz = 0;
		};
		bool is_empty() {
			return (sz == 0);
		};
		const CellType& operator[](std::size_t index) const { return data[index]; }
	};

	template <class T, typename CellType = std::pair<size_t, T>>
	class UnorderedTable : public TableByArray<T> {
	protected:
		using TableByArray<T>::data;
		using TableByArray<T>::sz;
	public:
		UnorderedTable() {
			sz = 0;
		}
		UnorderedTable(std::vector<CellType> v) {
			data = v;
			sz = v.size();
		}
		using TableByArray<T>::clear;
		using TableByArray<T>::get_size;
		using TableByArray<T>::is_empty;
		std::pair<std::size_t, T>* find(std::size_t key) {
			//try 
			{
				for (std::size_t i = 0; i < sz; i++) {
					if (data[i].first == key)
						return &data[i];
				}
				throw std::runtime_error("key_not_founded");
			}
			/*catch (const std::runtime_error& e) {
				std::cout << e.what() << std::endl;
				return nullptr;
			}*/
		};
		bool insert(std::size_t key, const T& value) override {
			for (std::size_t i = 0; i < sz; i++)
				if (data[i].first == key)
					return false;
			data.push_back(std::make_pair(key, value));
			sz++;
			return true;
		};
		bool erase(std::size_t key) override {
			for (std::size_t i = 0; i < sz; i++) {
				if (data[i].first == key) {
					swap(data[i], data[sz - 1]);
					data.pop_back();
					sz--;
					return true;
				}
			}
			return false;
		};
		friend std::ostream& operator<< (std::ostream& os, const UnorderedTable<T>& table) {
			for (std::size_t i = 0; i < table.get_size(); i++) {
				os << table[i].first << " | " << table[i].second << std::endl;
			}
			return os;
		};
		~UnorderedTable() {
			clear();
		};
	};


	template <class T, typename CellType = std::pair<size_t, T>>
	class OrderedTable : public TableByArray<T> {
	protected:
		using TableByArray<T>::data;
		using TableByArray<T>::sz;
	public:
		OrderedTable() {
			sz = 0;
		}
		OrderedTable(std::vector<CellType> v) {
			data = v;
			sz = v.size();
		}
		using TableByArray<T>::clear;
		using TableByArray<T>::get_size;
		using TableByArray<T>::is_empty;
		static bool f(const CellType& a, const CellType& b) {
			return (a.first < b.first);
		};
		std::pair<std::size_t, T>* find(std::size_t key) override {
			//try 
			{
				auto iterator = std::find_if(data.begin(), data.end(), [key](const CellType& item) {
					return item.first == key;
				});

				if (iterator != data.end())
					return &(*iterator);
				throw std::runtime_error("key_not_founded");
			}
			/*
			catch (const std::runtime_error& e) {
				std::cout << e.what() << std::endl;
				return nullptr;
			}
			*/

		};
		bool insert(std::size_t key, const T& value) override {
			auto iterator = std::lower_bound(data.begin(), data.end(), CellType(key, value),
				[](const CellType& a, const CellType& b) {
					return a.first < b.first;
				});

			if (iterator != data.end() && iterator->first == key)
				return false;

			data.insert(iterator, CellType(key, value));
			sz++;
			return true;
		};
		bool erase(std::size_t key) override {
			auto iterator = std::lower_bound(data.begin(), data.end(), CellType(key, T()),
				[](const CellType& a, const CellType& b) {
					return a.first < b.first;
				});

			if (iterator != data.end() && iterator->first == key) {
				data.erase(iterator);
				sz--;
				return true;
			}
			return false;
		};
		friend std::ostream& operator<< (std::ostream& os, const OrderedTable<T>& table) {
			for (std::size_t i = 0; i < table.get_size(); i++) 
				os << table[i].first << " | " << table[i].second << std::endl;
			return os;
		};
		~OrderedTable() {
			clear();
		};
	};

	template<class T>
	class HashTable : public TableByArray<T, std::list<std::pair<std::size_t, T>>> {
	protected:
		using TableByArray<T, std::list<std::pair<std::size_t, T>>>::data;
		using TableByArray<T, std::list<std::pair<std::size_t, T>>>::sz;
		static const std::size_t M = 100;
		std::size_t hashF(const std::size_t key) {
			std::size_t p = 41;
			std::size_t a, b;

			a = 0x5bd7e105 * (p - 2) + 1;
			b = a * (p - 1);

			return ((a * key ^ b) % p) % M;
		};
		size_t table_size = 0;
	public:
		HashTable() : table_size(0) {
			data.resize(100);
		};
		HashTable(std::size_t sz) : table_size(0) {
			data.resize(sz);
		}

		std::size_t get_size() const {
			return table_size;
		};
		void clear() {
			for (std::size_t i = 0; i < M; i++)
				if (!data[i].empty())
					data[i].clear();
		};
		bool is_empty() {
			return (table_size == 0);
		};
		std::pair<std::size_t, T>* find(std::size_t key) override {
			//try 
			{
				std::size_t index = hashF(key);

				auto iterator = data[index].begin();

				for (; iterator != data[index].end(); ++iterator)
					if (iterator->first == key)
						return &(*iterator);

				throw std::runtime_error("key_not_founded");
			}
			/*catch (const std::runtime_error& e) {
				std::cout << e.what() << std::endl;
				return nullptr;
			}*/
		};
		bool insert(std::size_t key, const T& value) override {
			std::size_t index = hashF(key);

			auto iterator = data[index].begin();

			for (; iterator != data[index].end(); ++iterator)
				if (iterator->first == key)
					return false;
			data[index].push_back(std::make_pair(key, value));
			table_size++;
			return true;
		};
		bool erase(std::size_t key) override {
			std::size_t index = hashF(key);

			auto iterator = data[index].begin();

			for (; iterator != data[index].end(); ++iterator)
				if (iterator->first == key) {
					data[index].erase(iterator);
					table_size--;
					return true;
				}
			return false;
		};

		friend std::ostream& operator<< (std::ostream& os, const HashTable<T>& table) {
			for (std::size_t i = 0; i < M; i++) {
				auto iterator = table.data[i].begin();
				for (; iterator != table.data[i].end(); ++iterator) 
					os << "(" << iterator->first << " | " << iterator->second << ")" << " --\\-- ";
				if (!table.data[i].empty())
					std::cout << std::endl;
			}
			return os;
		};
	};
}

