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

    node = astnode_create(PROGRAM, "hello, world");

    // test node
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(PROGRAM, node->type);
    TEST_ASSERT_NULL(node->children);
    TEST_ASSERT_NULL(node->next);
    TEST_ASSERT_NOT_NULL(node->ss);
    TEST_ASSERT_EQUAL(12, node->ss->len);
    TEST_ASSERT_EQUAL(MAX_NODE_LENGTH, node->ss->cap);
    TEST_ASSERT_EQUAL_STRING("hello, world", node->ss->buf);

    // destroy node
    astnode_destroy(&node);
    TEST_ASSERT_NULL(node);
}

void test_astnode_append_siblings(void) {
    struct ASTNode* child   = NULL;
    struct ASTNode* sibling = NULL;

    char* names[] = {"sib1", "sib2", "sib3", "sib4"};
    size_t sibs = 4;

    child = astnode_create(PROGRAM, "child");

    for (int i=0; i<sibs; ++i) {
        sibling = astnode_create(PROGRAM, names[i]);
        astnode_append_sibling(child, sibling);
    }

    //astnode_display(child, 0);

    astnode_destroy(&child);
    TEST_ASSERT_NULL(child);
}

void test_astnode_append_children(void) {
    struct ASTNode* root  = NULL;
    struct ASTNode* child = NULL;

    char*  gen1[] = { "A", "B", "C", "D" };
    size_t gen1_s = 4;

    char*  gen2[] = { "D", "E", "F" };
    size_t gen2_s = 3;

    char*  gen3[] = { "G" , "H" };
    size_t gen3_s = 2;


    root = astnode_create(PROGRAM, "root");
    for (int i=0; i<gen1_s; ++i) {
        child = astnode_create(PROGRAM, gen1[i]);
        astnode_append_child(root, child);
    }

    for (int i=0; i<gen2_s; ++i ) {
        child = astnode_create(PROGRAM, gen2[i]);
        astnode_append_child(root->children, child);
    }

    for (int i=0; i<gen3_s; ++i ) {
        child = astnode_create(PROGRAM, gen3[i]);
        astnode_append_child(root->children->next, child);
    }

    astnode_display(root, 0);

    astnode_destroy(&root);
    TEST_ASSERT_NULL(root);
}

void test_astnode_append_children_and_siblings(void) {

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_astnode_create_and_destroy);
    RUN_TEST(test_astnode_append_siblings);
    RUN_TEST(test_astnode_append_children);

    return UNITY_END();
}
