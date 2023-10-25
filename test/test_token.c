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

void test_tokenlist_create_and_destroy(void) {
    struct TokenList *tl = tokenlist_create();

    TEST_ASSERT_NULL(tl->head);
    TEST_ASSERT_NULL(tl->tail);
    TEST_ASSERT_EQUAL(0, tl->len);

    tokenlist_destroy(&tl);
    TEST_ASSERT_NULL(tl);
}

void test_tokenlist_append(void) {
    struct TokenList *tl  = tokenlist_create();
    struct SafeString *ss = safestring_create(32);

    char *wds[]    = {"hello world", "goodbye", "my token"};
    size_t wds_len = 3;

    for (int i=0; i<wds_len; ++i) {
        safestring_set(ss, wds[i]);
        tokenlist_append(tl, TOKEN_IDENTIFIER, ss);
    }

    TEST_ASSERT_EQUAL(3, tl->len);

    TEST_ASSERT_EQUAL_STRING("hello world", tl->head->ss->buf);
    TEST_ASSERT_EQUAL(11, tl->head->ss->len);
    TEST_ASSERT_EQUAL(12, tl->head->ss->cap);
    TEST_ASSERT_NOT_NULL(tl->head->next);

    TEST_ASSERT_EQUAL_STRING("my token", tl->tail->ss->buf);
    TEST_ASSERT_EQUAL(8, tl->tail->ss->len);
    TEST_ASSERT_EQUAL(9, tl->tail->ss->cap);
    TEST_ASSERT_NULL(tl->tail->next);

    // destroy safestring
    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);

    // destroy tokenlist
    tokenlist_destroy(&tl);
    TEST_ASSERT_NULL(tl);

}

void test_tokenlist_append_to_empty_tokenlist(void) {
    struct TokenList *tl = NULL;
    struct SafeString *ss = safestring_create(32);
    
    TEST_ASSERT_EQUAL(1, tokenlist_append(tl, TOKEN_IDENTIFIER, ss));

    // destroy safestring
    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_token_create_and_destroy);
    RUN_TEST(test_token_create_with_invalid_safestring);

    RUN_TEST(test_tokenlist_create_and_destroy);
    RUN_TEST(test_tokenlist_append);
    RUN_TEST(test_tokenlist_append_to_empty_tokenlist);

    return UNITY_END();
}
