#include "tables.h"
#include <gtest.h>

template<typename Item>
class Ordered_Table_Test : public ::testing::Test {
protected:

	void SetUp() {
		table = new maps::OrderedTable<Item>;
	}

	void TearDown() {
		delete table;
	}

	maps::OrderedTable<Item>* table;
};

TYPED_TEST_CASE_P(Ordered_Table_Test);

TYPED_TEST_P(Ordered_Table_Test, create_ordered_table) {
	ASSERT_NO_THROW(this->SetUp());
};
TYPED_TEST_P(Ordered_Table_Test, insert_ordered_table) {
	this->SetUp();

	ASSERT_NO_THROW((*this->table).insert(10, "Brooklyn"));
};
TYPED_TEST_P(Ordered_Table_Test, find_ordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ(((*this->table).find(10))->second, "Brooklyn");
};
TYPED_TEST_P(Ordered_Table_Test, throw_find_ordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).find(12), nullptr);
};
TYPED_TEST_P(Ordered_Table_Test, throw_insert_ordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).insert(10, "Montana"), 0);
};
TYPED_TEST_P(Ordered_Table_Test, erase_ordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	EXPECT_EQ((*this->table).erase(10), 1);
}
TYPED_TEST_P(Ordered_Table_Test, throw_erase_ordered_table) {
	this->SetUp();
	EXPECT_EQ((*this->table).erase(10), 0);
}
TYPED_TEST_P(Ordered_Table_Test, clear_ordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	ASSERT_NO_THROW((*this->table).clear());
}
TYPED_TEST_P(Ordered_Table_Test, is_empty_ordered_table) {
	this->SetUp();
	EXPECT_EQ((*this->table).is_empty(), 1);
}
TYPED_TEST_P(Ordered_Table_Test, get_size_ordered_table) {
	this->SetUp();
	(*this->table).insert(10, "Brooklyn");
	(*this->table).insert(5, "Montana");

	EXPECT_EQ((*this->table).get_size(), 2);
}
TYPED_TEST_P(Ordered_Table_Test, get_size_ordered_table_is_empty) {
	this->SetUp();

	EXPECT_EQ((*this->table).get_size(), 0);
}


REGISTER_TYPED_TEST_CASE_P(Ordered_Table_Test, create_ordered_table, insert_ordered_table, find_ordered_table,
	throw_find_ordered_table, throw_insert_ordered_table, erase_ordered_table, throw_erase_ordered_table, clear_ordered_table,
	is_empty_ordered_table, get_size_ordered_table, get_size_ordered_table_is_empty);

typedef ::testing::Types<std::string> ContainerTypes;
INSTANTIATE_TYPED_TEST_CASE_P(ContainerTypesInstantiation, Ordered_Table_Test, ContainerTypes);