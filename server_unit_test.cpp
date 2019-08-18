#include "../server.h"
#include "../hasher_impl.h"

#include <gtest/gtest.h>

TEST(CreateServerTest, ServerCreation)
{
    Server::ServerPtr server;
    ASSERT_NO_THROW(server = CreateServer(0));
    ASSERT_TRUE(server.get() != nullptr);
}

TEST(ServerNoErrorTest, ServerEmptyError)
{
    Server::ServerPtr server;
    ASSERT_NO_THROW(server = CreateServer(0));
    ASSERT_TRUE(server->GetErrorText().empty());
}

TEST(HasherStabilityTest, HasherStabilityTest)
{
    StringHasher hasher1;
    hasher1.AddData("string1");
    StringHasher hasher2;
    hasher2.AddData("string1");
    ASSERT_TRUE(hasher1.GetHash() == hasher2.GetHash());
}

TEST(EmptyHasherTest, EmptyHasherTest)
{
    StringHasher hasher;
    ASSERT_TRUE(hasher.GetHash() != "");
}

TEST(AddingDataToHasherTest, EmptyHasherTest)
{
    StringHasher hasher;
    auto emptyHash = hasher.GetHash();
    hasher.AddData("some data");
    hasher.Clear();
    ASSERT_TRUE(emptyHash == hasher.GetHash());
}
