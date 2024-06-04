#include <gtest/gtest.h>
#include <hilti/rt/libhilti.h>
#include <spicy/rt/libspicy.h>
#include <spicy_protobuf.h>
#include <test-data/varint/protobuf_150.h>

namespace { // anonymous namespace

class SpicyProtobufTest : public ::testing::Test {
protected:
  static void SetUpTestSuite();
  static void TearDownTestSuite();
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

TEST_F(SpicyProtobufTest, TestVarInt) {
  auto p_input_stream = hilti::rt::reference::make_value<hilti::rt::Stream>(reinterpret_cast<const char*>(varint_protobuf_150_binpb), varint_protobuf_150_binpb_len);
  p_input_stream->freeze();
  auto p_data = hilti::rt::reference::make_value<__hlt::protobuf::Message>();
  hlt::protobuf::Message::parse2(p_data, p_input_stream, {}, {});
  ASSERT_EQ(p_data->message->size(), 1);
  auto tag_and_val = p_data->message->at(0);
  EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
  EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), __hlt::protobuf::WireType::VARINT);
  ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
  EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 150);
  EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 150);
  EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 150);
  EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 75);
}

} // anonymous namespace
