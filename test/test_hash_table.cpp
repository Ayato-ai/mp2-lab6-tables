#include "tables.h"
#include <gtest.h>

template<typename Item>
class Hash_Table_Test : public ::testing::Test {
protected:
	void SetUp() {
		table = new maps::HashTable<Item>;
	}

	void TearDown() {
		delete table;
	}

	maps::HashTable<Item>* table;
};

TYPED_TEST_CASE_P(Hash_Table_Test);

TYPED_TEST_P(Hash_Table_Test, create_hash_table) {
	ASSERT_NO_THROW(this->SetUp());
};
TYPED_TEST_P(Hash_Table_Test, insert_hash_table) {
	this->SetUp();

	ASSERT_NO_THROW((*this->table).insert(10, "Brooklyn"));
};
TYPED_TEST_P(Hash_Table_Test, find_hash_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ(((*this->table).find(10))->second, "Brooklyn");
};
TYPED_TEST_P(Hash_Table_Test, throw_find_hash_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).find(12), nullptr);
};
TYPED_TEST_P(Hash_Table_Test, throw_insert_hash_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).insert(10, "Montana"), 0);
};
TYPED_TEST_P(Hash_Table_Test, erase_hash_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).erase(10), 1);
}
TYPED_TEST_P(Hash_Table_Test, throw_erase_hash_table) {
	this->SetUp();
	EXPECT_EQ((*this->table).erase(10), 0);
}
TYPED_TEST_P(Hash_Table_Test, clear_hash_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	ASSERT_NO_THROW((*this->table).clear());
}
TYPED_TEST_P(Hash_Table_Test, is_empty_hash_table) {
	this->SetUp();
	EXPECT_EQ((*this->table).is_empty(), 1);
}
TYPED_TEST_P(Hash_Table_Test, get_size_hash_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	(*this->table).insert(5, "Montana");

	EXPECT_EQ((*this->table).get_size(), 2);
}
TYPED_TEST_P(Hash_Table_Test, get_size_hash_table_is_empty) {
	this->SetUp();

	EXPECT_EQ((*this->table).get_size(), 0);
}



REGISTER_TYPED_TEST_CASE_P(Hash_Table_Test, create_hash_table, insert_hash_table, find_hash_table,
	throw_find_hash_table, throw_insert_hash_table, erase_hash_table, throw_erase_hash_table, clear_hash_table,
	is_empty_hash_table, get_size_hash_table, get_size_hash_table_is_empty);

typedef ::testing::Types<std::string> ContainerTypes;
INSTANTIATE_TYPED_TEST_CASE_P(ContainerTypesInstantiation, Hash_Table_Test, ContainerTypes);