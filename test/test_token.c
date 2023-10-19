#include "../src/token.h"
#include "../unity/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_token_create_and_destroy(void) {
    struct SafeString *ss = NULL;
    struct Token *tok     = NULL;

    // create safestring
    ss = safestring_create(32);
    safestring_set(ss, "hello, world");

    // create token using safestring
    tok = token_create(TOKEN_IDENTIFIER, ss);

    // destroy safestring
    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);

    // check token
    TEST_ASSERT_EQUAL(12, tok->ss->len);
    TEST_ASSERT_EQUAL(13, tok->ss->cap);
    TEST_ASSERT_EQUAL_STRING("hello, world", tok->ss->buf);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER, tok->type);
    TEST_ASSERT_NULL(tok->next);

    // destroy token
    token_destroy(&tok);
    TEST_ASSERT_NULL(tok);
}

void test_token_create_with_invalid_safestring(void) {
    struct SafeString *ss = NULL;
    struct Token *tok     = NULL;
    int err;

    // create overflowing safestring
    ss = safestring_create(5);
    err = safestring_set(ss, "hello, world"); // insufficient space, returns 1; ss->buff = ""
    TEST_ASSERT_EQUAL(1, err);
    TEST_ASSERT_EQUAL(5, ss->cap);
    TEST_ASSERT_EQUAL(0, ss->len);
    TEST_ASSERT_EQUAL_STRING("", ss->buf);

    // create token with empty safestring
    tok = token_create(TOKEN_IDENTIFIER, ss);

    // destroy safestring
    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);

    // check token
    TEST_ASSERT_NULL(tok);

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_token_create_and_destroy);
    RUN_TEST(test_token_create_with_invalid_safestring);

    return UNITY_END();
}
