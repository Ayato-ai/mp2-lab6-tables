#include "tables.h"
#include <gtest.h>

template<typename Item>
class Unordered_Table_Test : public ::testing::Test {
protected:

	void SetUp() {
		table = new maps::UnorderedTable<Item>;
	}
	
	void TearDown() {
		delete table;
	}

	maps::UnorderedTable<Item>* table;
};

TYPED_TEST_CASE_P(Unordered_Table_Test);

TYPED_TEST_P(Unordered_Table_Test, create_unordered_table) {
	ASSERT_NO_THROW(this->SetUp());
};
TYPED_TEST_P(Unordered_Table_Test, insert_unordered_table) {
	this->SetUp();

	ASSERT_NO_THROW((*this->table).insert(10, "Brooklyn"));
};
TYPED_TEST_P(Unordered_Table_Test, find_unordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ(((*this->table).find(10))->second, "Brooklyn");
};
TYPED_TEST_P(Unordered_Table_Test, throw_find_unordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	ASSERT_ANY_THROW((*this->table).find(12));
};
TYPED_TEST_P(Unordered_Table_Test, throw_insert_unordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).insert(10, "Montana"), 0);
};
TYPED_TEST_P(Unordered_Table_Test, erase_unordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).erase(10), 1);
}
TYPED_TEST_P(Unordered_Table_Test, throw_erase_unordered_table) {
	this->SetUp();
	EXPECT_EQ((*this->table).erase(10), 0);
}
TYPED_TEST_P(Unordered_Table_Test, clear_unordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	ASSERT_NO_THROW((*this->table).clear());
}
TYPED_TEST_P(Unordered_Table_Test, is_empty_unordered_table) {
	this->SetUp();
	EXPECT_EQ((*this->table).is_empty(), 1);
}
TYPED_TEST_P(Unordered_Table_Test, get_size_unordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	(*this->table).insert(5, "Montana");

	EXPECT_EQ((*this->table).get_size(), 2);
}
TYPED_TEST_P(Unordered_Table_Test, get_size_unordered_table_is_empty) {
	this->SetUp();

	EXPECT_EQ((*this->table).get_size(), 0);
}


REGISTER_TYPED_TEST_CASE_P(Unordered_Table_Test, create_unordered_table, insert_unordered_table, find_unordered_table,
	throw_find_unordered_table, throw_insert_unordered_table, erase_unordered_table, throw_erase_unordered_table, clear_unordered_table,
	is_empty_unordered_table, get_size_unordered_table, get_size_unordered_table_is_empty);

typedef ::testing::Types<std::string> ContainerTypes;
INSTANTIATE_TYPED_TEST_CASE_P(ContainerTypesInstantiation, Unordered_Table_Test, ContainerTypes);