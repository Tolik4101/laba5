#include <iostream>
#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct MockAccount:public Account
{
	MockAccount(int id, int balance):Account(id, balance){}
	MOCK_METHOD1(ChangeBalance, void(int diff));
	MOCK_METHOD0(GetBalance, int());
	MOCK_METHOD0(id, int());
	MOCK_METHOD0(Lock, void());
	MOCK_METHOD0(Unlock, void()); 
};

struct MockTransaction:public Transaction
{
	MOCK_METHOD1(set_fee, void(int fee));
	MOCK_METHOD0(fee, int());
	MOCK_METHOD3(Make, bool(Account& from, Account& to, int sum)); 
};

TEST(Account, Test1)
{
	Account sber(1, 120);
	sber.Lock();
	EXPECT_EQ(sber.GetBalance(),120);
	EXPECT_EQ(sber.id(),1);
	sber.ChangeBalance(23);
	EXPECT_EQ(sber.GetBalance(),143);
	sber.ChangeBalance(-23);
 	EXPECT_EQ(sber.GetBalance(),120);
	sber.Unlock();
}
TEST(Account, Test2)
{
	Account tink(1, 200);
	tink.Lock();
	ASSERT_NO_THROW(tink.ChangeBalance(12));
	EXPECT_EQ(tink.GetBalance(),212);
	ASSERT_NO_THROW(tink.ChangeBalance(-12));
        EXPECT_EQ(tink.GetBalance(),200);
	tink.Unlock();
	ASSERT_ANY_THROW(tink.ChangeBalance(15));
        EXPECT_EQ(tink.GetBalance(),200);
}
TEST(Account, Test3)
{
	MockAccount tink(13, 131);
	EXPECT_CALL(tink, Lock()).Times(1);
    	EXPECT_CALL(tink, GetBalance()).Times(2);
    	EXPECT_CALL(tink, ChangeBalance(testing::_)).Times(2);
    	EXPECT_CALL(tink, Unlock()).Times(1);
    	tink.Lock();
    	tink.GetBalance();
    	tink.ChangeBalance(100000);
    	tink.GetBalance();
    	tink.Unlock();
    	tink.ChangeBalance(1000);
}
TEST(Transaction, Test4)
{
	Transaction uralsib;
	Account bmstu(14, 201);
	Account mirea(16, 122);
	EXPECT_EQ(uralsib.Make(bmstu, mirea, 101), true);
	EXPECT_EQ(uralsib.Make(mirea, bmstu, 101), true);
	ASSERT_ANY_THROW(uralsib.Make(bmstu, bmstu, 120));
        ASSERT_ANY_THROW(uralsib.Make(mirea, bmstu, 50));
        ASSERT_ANY_THROW(uralsib.Make(mirea, bmstu, -100));	
}
TEST(Transaction, Test5)
{
	Transaction rosbank;
	Account mfti(12, 322);
	Account mifi(32, 422);
	rosbank.set_fee(0);
	EXPECT_EQ(rosbank.fee(), 0);
	rosbank.Make(mfti, mifi, 120);
	EXPECT_EQ(mifi.GetBalance(), 542);
	EXPECT_EQ(mfti.GetBalance(), 302);
}
TEST(Transaction, Test6)
{
	MockTransaction bog;
	MockAccount mgu(18, 300);
	MockAccount vse(32,544);
	EXPECT_CALL(bog, set_fee(testing::_)).Times(1);
    	EXPECT_CALL(bog, Make(testing::_, testing::_, testing::_)).Times(1);
    	EXPECT_CALL(bog, fee()).Times(1);
	EXPECT_CALL(mgu, GetBalance()).Times(1);
   	EXPECT_CALL(vse, GetBalance()).Times(1);
	bog.set_fee(20);
    	bog.Make(mgu, vse, 100);
    	bog.fee();
    	mgu.GetBalance();
    	vse.GetBalance();
}
