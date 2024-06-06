#include <gtest/gtest.h>
#include <hilti/rt/libhilti.h>
#include <hilti/rt/types/reference.h>
#include <spicy/rt/libspicy.h>
#include <spicy_protobuf.h>
#include <test-data/varint/protobuf_150.h>
#include <test-data/varint/protobuf_1500.h>
#include <test-data/varint/protobuf_1500000.h>
#include <test-data/varint/protobuf_bools.h>
#include <test-data/varint/protobuf_large_field_num.h>
#include <test-data/varint/protobuf_max_uint.h>
#include <test-data/varint/protobuf_neg_1.h>
#include <test-data/varint/protobuf_neg_2.h>
#include <test-data/varint/protobuf_neg_150.h>
#include <test-data/varint/protobuf_zigzag_150.h>

namespace { // anonymous namespace

using ::hilti::rt::ValueReference;
using ::__hlt::protobuf::Message;

class SpicyProtobufTest : public ::testing::Test {
protected:

  static auto SetUpTestSuite() -> void;
  static auto TearDownTestSuite() -> void;

  static auto parseMessage(const char* data, uint64_t size) -> ValueReference<Message>;
};

auto SpicyProtobufTest::SetUpTestSuite() -> void {
  // Initialize runtime libraries
  ::hilti::rt::init();
  ::spicy::rt::init();
}

auto SpicyProtobufTest::TearDownTestSuite() -> void {
  // Tear down runtime libraries
  ::spicy::rt::done();
  ::hilti::rt::done();
}

auto SpicyProtobufTest::parseMessage(const char* p_data, uint64_t const size) -> ValueReference<Message> {
  using namespace ::hilti::rt::reference;
  using ::hilti::rt::Stream;

  auto p_input_stream = make_value<Stream>(p_data, size);
  p_input_stream->freeze();
  auto p_msg = make_value<Message>();
  ::hlt::protobuf::Message::parse2(p_msg, p_input_stream, {}, {});
  return p_msg;
}

TEST_F(SpicyProtobufTest, TestVarIntPositive) {
  using namespace __hlt::protobuf;

  { // protobuf_150
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_150_binpb), varint_protobuf_150_binpb_len);
    ASSERT_EQ(p_data->message->size(), 1);
    auto tag_and_val = p_data->message->at(0);
    EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
    EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
    ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 150);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 150);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 150);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 75);
  }

  { // protobuf_1500
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_1500_binpb), varint_protobuf_1500_binpb_len);
    ASSERT_EQ(p_data->message->size(), 1);
    auto tag_and_val = p_data->message->at(0);
    EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
    EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
    ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 1500);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 1500);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 1500);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 750);
  }

  { // protobuf_1500000
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_1500000_binpb), varint_protobuf_1500000_binpb_len);
    ASSERT_EQ(p_data->message->size(), 1);
    auto tag_and_val = p_data->message->at(0);
    EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
    EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
    ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 1500000);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 1500000);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 1500000);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 750000);
  }

}

TEST_F(SpicyProtobufTest, TestVarIntBool) {
  using namespace __hlt::protobuf;

  { // protobuf_bools
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_bools_binpb), varint_protobuf_bools_binpb_len);
    ASSERT_EQ(p_data->message->size(), 2);
    { // First TagAndValue
      auto tag_and_val = p_data->message->at(0);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, -1);
    }

    { // Second TagAndValue
      auto tag_and_val = p_data->message->at(1);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 2);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 0);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 0);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 0);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 0);
    }
  }
}

TEST_F(SpicyProtobufTest, TestVarIntLargeFieldNum) {
  using namespace __hlt::protobuf;

  { // protobuf_large_field_num
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_large_field_num_binpb), varint_protobuf_large_field_num_binpb_len);
    ASSERT_EQ(p_data->message->size(), 2);
    { // First TagAndValue
      auto tag_and_val = p_data->message->at(0);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 63);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, -1);
    }

    { // Second TagAndValue
      auto tag_and_val = p_data->message->at(1);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 1000);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, -1);
    }
  }
}

TEST_F(SpicyProtobufTest, TestVarIntMaxUint) {
  using namespace __hlt::protobuf;

  { // protobuf_max_uint
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_max_uint_binpb), varint_protobuf_max_uint_binpb_len);
    ASSERT_EQ(p_data->message->size(), 1);
    auto tag_and_val = p_data->message->at(0);
    EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
    EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
    ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 18446744073709551615ull);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, -1);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, -1);
    // The signed zigzag value can't be represented in 64 bits, so skipping it.
  }
}

TEST_F(SpicyProtobufTest, TestVarIntNegative) {
  using namespace __hlt::protobuf;

  { // protobuf_neg_1
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_neg_1_binpb), varint_protobuf_neg_1_binpb_len);
    ASSERT_EQ(p_data->message->size(), 3);
    { // First TagAndValue
      auto tag_and_val = p_data->message->at(0);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 4294967295);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, -1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 4294967295);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, -2147483648);
    }

    { // Second TagAndValue
      auto tag_and_val = p_data->message->at(1);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 2);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 18446744073709551615ull);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, -1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, -1);
      // ZigZag too long to be represented in 64 bits
    }

    { // Third TagAndValue
      auto tag_and_val = p_data->message->at(2);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 3);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 18446744073709551615ull);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, -1);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, -1);
      // ZigZag too long to be represented in 64 bits
    }
  }

  { // protobuf_neg_2
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_neg_2_binpb), varint_protobuf_neg_2_binpb_len);
    ASSERT_EQ(p_data->message->size(), 2);
    { // First TagAndvalue
      auto tag_and_val = p_data->message->at(0);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 18446744073709551614ull);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, -2);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, -2);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 9223372036854775807ull);
    }

    { // Second TagAndvalue
      auto tag_and_val = p_data->message->at(1);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 3);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 3);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 3);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, -2);
    }
  }

  { // protobuf_neg_150
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_neg_150_binpb), varint_protobuf_neg_150_binpb_len);
    ASSERT_EQ(p_data->message->size(), 1);
    auto tag_and_val = p_data->message->at(0);
    EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
    EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
    ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 18446744073709551466ull);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, -150);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, -150);
    EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 9223372036854775733ull);
  }
}

TEST_F(SpicyProtobufTest, TestVarIntZigZag) {
  using namespace __hlt::protobuf;

  { // protobuf_zigzag_150
    auto p_data = parseMessage(reinterpret_cast<const char *>(varint_protobuf_zigzag_150_binpb), varint_protobuf_zigzag_150_binpb_len);
    ASSERT_EQ(p_data->message->size(), 2);
    { // First TagAndvalue
      auto tag_and_val = p_data->message->at(0);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 1);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 299);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 299);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 299);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, -150);
    }

    { // Second TagAndvalue
      auto tag_and_val = p_data->message->at(1);
      EXPECT_EQ(tag_and_val.tag.value()->field_num, 2);
      EXPECT_EQ(tag_and_val.tag.value()->wire_type.value(), WireType::VARINT);
      ASSERT_FALSE(tag_and_val.value.value()->varint->isNull());
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_unsigned, 300);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment32, 300);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_twos_compliment64, 300);
      EXPECT_EQ(tag_and_val.value.value()->varint.value()->as_zigzag, 150);
    }
  }
}

} // anonymous namespace
