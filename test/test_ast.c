#include "../src/ast.h"
#include "../unity/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_astnode_create_and_destroy(void) {
    struct ASTNode* node  = NULL;
    struct SafeString *ss = NULL;

    ss = safestring_create(32);
    safestring_set(ss, "my identifier");

    node = astnode_create(PROGRAM, ss);

    // destroy safestring
    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);
    
    // test node
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(PROGRAM, node->type);
    TEST_ASSERT_NULL(node->children);
    TEST_ASSERT_NULL(node->next);
    TEST_ASSERT_EQUAL(13, node->ss->len);
    TEST_ASSERT_EQUAL(14, node->ss->cap);
    TEST_ASSERT_EQUAL_STRING("my identifier", node->ss->buf);

    // destroy node
    astnode_destroy(&node);
    TEST_ASSERT_NULL(node);
}

void test_astnode_append_siblings(void) {
    struct ASTNode* child = NULL;
    struct SafeString* ss = NULL;

    char* names[] = {"sib1", "sib2", "sib3", "sib4"};
    size_t sibs = 4;

    ss = safestring_create(32);
    safestring_set(ss, "child");
    child = astnode_create(PROGRAM, ss);

    for (int i=0; i<sibs; ++i) {
        safestring_set(ss, names[i]);
        astnode_append_sibling(child, PROGRAM, ss);
    }

    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);

    //astnode_display(child, 0);

    astnode_destroy(&child);
    TEST_ASSERT_NULL(child);
}

void test_astnode_append_children(void) {
    struct ASTNode* root = NULL;
    struct SafeString* ss = NULL;

    char* gen1[]   = { "A", "B", "C", "D" };
    size_t gen1_s = 4;

    char* gen2[]   = { "D", "E", "F" };
    size_t gen2_s  = 3;

    char* gen3[]   = { "G" , "H" };
    size_t gen3_s    = 2;


    ss = safestring_create(32);
    safestring_set(ss, "root");
    root = astnode_create(PROGRAM, ss);
    for (int i=0; i<gen1_s; ++i) {
        safestring_set(ss, gen1[i]);
        astnode_append_child(root, PROGRAM, ss);
    }

    for (int i=0; i<gen2_s; ++i ) {
        safestring_set(ss, gen2[i]);
        astnode_append_child(root->children, PROGRAM, ss);
    }

    for (int i=0; i<gen3_s; ++i ) {
        safestring_set(ss, gen3[i]);
        astnode_append_child(root->children->next, PROGRAM, ss);
    }

    safestring_destroy(&ss);
    TEST_ASSERT_NULL(ss);

    astnode_display(root, 0);

    astnode_destroy(&root);
    TEST_ASSERT_NULL(root);
}

void test_astnode_append_children_and_siblines(void) {
    struct ASTNode* root = NULL;
    struct SafeString* ss = NULL;


}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_astnode_create_and_destroy);
    RUN_TEST(test_astnode_append_siblings);
    RUN_TEST(test_astnode_append_children);

    return UNITY_END();
}
