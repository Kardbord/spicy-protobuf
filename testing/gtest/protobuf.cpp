#include <gtest/gtest.h>
#include <hilti/rt/init.h>
#include <spicy/rt/init.h>
#include <spicy_protobuf.h>

namespace { // anonymous namespace

class SpicyProtobufTest : public ::testing::Test {
protected:
  static void SetUpTestSuite();
  static void TearDownTestSuite();

  void SetUp() override;
  void TearDown() override;
};

void SpicyProtobufTest::SetUpTestSuite() {
  // Initialize runtime libraries
  ::hilti::rt::init();
  ::spicy::rt::init();
}

void SpicyProtobufTest::TearDownTestSuite() {
  // Tear down runtime libraries
  ::spicy::rt::done();
  ::hilti::rt::done();
}

void SpicyProtobufTest::SetUp() {

}

void SpicyProtobufTest::TearDown() {

}

} // anonymous namespace
