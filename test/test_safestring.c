#include "../src/safestring.h"
#include "../unity/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_safestring_create_and_destroy(void) {
    struct SafeString* ss = safestring_create(10);
    TEST_ASSERT_EQUAL(10, ss->cap);
    TEST_ASSERT_EQUAL_STRING("", ss->buf);
    TEST_ASSERT_EQUAL(0, ss->len);
    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);
}

void test_safestring_create_with_0_length(void) {
    struct SafeString* ss = safestring_create(0);
    TEST_ASSERT_EQUAL(0, ss->cap);
    TEST_ASSERT_EQUAL_STRING("", ss->buf);
    TEST_ASSERT_EQUAL(0, ss->len);
    safestring_destroy(&ss);
}

void test_safestring_set_for_strings_less_than_cap(void) {
    struct SafeString* ss = safestring_create(10);

    TEST_ASSERT_EQUAL(0, safestring_set(ss, "hello"));
    TEST_ASSERT_EQUAL(5, ss->len);
    TEST_ASSERT_EQUAL_STRING("hello", ss->buf);

    TEST_ASSERT_EQUAL(0, safestring_set(ss, "hola"));
    TEST_ASSERT_EQUAL(4, ss->len);
    TEST_ASSERT_EQUAL_STRING("hola", ss->buf);

    TEST_ASSERT_EQUAL(0, safestring_set(ss, ""));
    TEST_ASSERT_EQUAL(0, ss->len);
    TEST_ASSERT_EQUAL_STRING("", ss->buf);

    TEST_ASSERT_EQUAL(0, safestring_set(ss, "howdeedo"));
    TEST_ASSERT_EQUAL(8, ss->len);
    TEST_ASSERT_EQUAL_STRING("howdeedo", ss->buf);

    safestring_destroy(&ss);
}

void test_safestring_set_for_strings_equal_to_cap(void) {
    struct SafeString* ss = safestring_create(10);

    TEST_ASSERT_EQUAL(0, safestring_set(ss, "abcdefghi"));
    TEST_ASSERT_EQUAL(9, ss->len);
    TEST_ASSERT_EQUAL_STRING("abcdefghi", ss->buf);

    safestring_destroy(&ss);
}

void test_safestring_set_for_strings_greater_than_cap(void) {
    struct SafeString* ss = safestring_create(10);

    // invalid - does not update buf or len
    TEST_ASSERT_EQUAL(1, safestring_set(ss, "abcdefghij"));
    TEST_ASSERT_EQUAL(0, ss->len);
    TEST_ASSERT_EQUAL_STRING("", ss->buf);

    // valid - updates buf and len
    TEST_ASSERT_EQUAL(0, safestring_set(ss, "abcdefghi"));
    TEST_ASSERT_EQUAL(9, ss->len);
    TEST_ASSERT_EQUAL_STRING("abcdefghi", ss->buf);

    // invalid - does not update buf or len
    TEST_ASSERT_EQUAL(1, safestring_set(ss, "abcdefghij"));
    TEST_ASSERT_EQUAL(9, ss->len);
    TEST_ASSERT_EQUAL_STRING("abcdefghi", ss->buf);

    safestring_destroy(&ss);
}


void test_safestring_append_in_valid_cases(void) {
    struct SafeString* ss = safestring_create(10);

    TEST_ASSERT_EQUAL(0, safestring_appendc(ss, 'a'));
    TEST_ASSERT_EQUAL(1, ss->len);
    TEST_ASSERT_EQUAL_STRING("a", ss->buf);

    TEST_ASSERT_EQUAL(0, safestring_appendc(ss, 'b'));
    TEST_ASSERT_EQUAL(2, ss->len);
    TEST_ASSERT_EQUAL_STRING("ab", ss->buf);

    TEST_ASSERT_EQUAL(0, safestring_appendc(ss, 'c'));
    TEST_ASSERT_EQUAL(3, ss->len);
    TEST_ASSERT_EQUAL_STRING("abc", ss->buf);

    TEST_ASSERT_EQUAL(0, safestring_set(ss, "xyz"));
    TEST_ASSERT_EQUAL(3, ss->len);
    TEST_ASSERT_EQUAL_STRING("xyz", ss->buf);
    TEST_ASSERT_EQUAL(0, safestring_appendc(ss, 'a'));
    TEST_ASSERT_EQUAL(4, ss->len);
    TEST_ASSERT_EQUAL_STRING("xyza", ss->buf);

    safestring_destroy(&ss);
}

void test_safestring_append_in_invalid_cases(void) {
    struct SafeString* ss = safestring_create(3);

    TEST_ASSERT_EQUAL(0, safestring_appendc(ss, 'a'));
    TEST_ASSERT_EQUAL(1, ss->len);
    TEST_ASSERT_EQUAL_STRING("a", ss->buf);

    TEST_ASSERT_EQUAL(0, safestring_appendc(ss, 'b'));
    TEST_ASSERT_EQUAL(2, ss->len);
    TEST_ASSERT_EQUAL_STRING("ab", ss->buf);

    TEST_ASSERT_EQUAL(1, safestring_appendc(ss, 'c'));
    TEST_ASSERT_EQUAL(2, ss->len);
    TEST_ASSERT_EQUAL_STRING("ab", ss->buf);

    safestring_destroy(&ss);
}

void test_safestring_reset(void) {
    struct SafeString* ss = safestring_create(10);

    safestring_set(ss, "hello");
    safestring_set(ss, "");
    safestring_appendc(ss, '1');

    TEST_ASSERT_EQUAL_STRING("1", ss->buf);

    safestring_destroy(&ss);
}

void test_safestring_append_for_valid_strings(void) {
    struct SafeString* ss = safestring_create(20);
    size_t err = 0;

    TEST_ASSERT_NOT_NULL(ss);
    TEST_ASSERT_EQUAL(0, ss->len);
    TEST_ASSERT_EQUAL(20, ss->cap);
    TEST_ASSERT_EQUAL_STRING("", ss->buf);

    err = safestring_set(ss, "hello");
    TEST_ASSERT_EQUAL(0, err);
    TEST_ASSERT_EQUAL(5, ss->len);
    TEST_ASSERT_EQUAL(20, ss->cap);
    TEST_ASSERT_EQUAL_STRING("hello", ss->buf);

    err = safestring_append(ss, ", world");
    TEST_ASSERT_EQUAL(0, err);
    TEST_ASSERT_EQUAL(12, ss->len);
    TEST_ASSERT_EQUAL(20, ss->cap);
    TEST_ASSERT_EQUAL_STRING("hello, world", ss->buf);

    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);
}

void test_safestring_append_for_invalid_strings(void) {
    struct SafeString* ss = safestring_create(10);
    size_t err = 0;

    TEST_ASSERT_NOT_NULL(ss);
    TEST_ASSERT_EQUAL(0, ss->len);
    TEST_ASSERT_EQUAL(10, ss->cap);
    TEST_ASSERT_EQUAL_STRING("", ss->buf);

    err = safestring_set(ss, "hello");
    TEST_ASSERT_EQUAL(0, err);
    TEST_ASSERT_EQUAL(5, ss->len);
    TEST_ASSERT_EQUAL(10, ss->cap);
    TEST_ASSERT_EQUAL_STRING("hello", ss->buf);

    err = safestring_append(ss, ", world");
    TEST_ASSERT_EQUAL(1, err);
    TEST_ASSERT_EQUAL(5, ss->len);
    TEST_ASSERT_EQUAL(10, ss->cap);
    TEST_ASSERT_EQUAL_STRING("hello", ss->buf);

    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_safestring_create_and_destroy);
    RUN_TEST(test_safestring_create_with_0_length);
    RUN_TEST(test_safestring_set_for_strings_less_than_cap);
    RUN_TEST(test_safestring_set_for_strings_equal_to_cap);
    RUN_TEST(test_safestring_set_for_strings_greater_than_cap);
    RUN_TEST(test_safestring_append_in_valid_cases);
    RUN_TEST(test_safestring_append_in_invalid_cases);
    RUN_TEST(test_safestring_reset);

    RUN_TEST(test_safestring_append_for_valid_strings);
    RUN_TEST(test_safestring_append_for_invalid_strings);

    return UNITY_END();
}
