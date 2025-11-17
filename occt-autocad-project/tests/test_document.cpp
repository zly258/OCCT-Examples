#include <gtest/gtest.h>
#include "Document.h"

class DocumentTest : public ::testing::Test {
protected:
    Document* doc;

    void SetUp() override {
        doc = new Document();
    }

    void TearDown() override {
        delete doc;
    }
};

TEST_F(DocumentTest, TestInitialization) {
    EXPECT_EQ(doc->GetTitle(), "");
    EXPECT_EQ(doc->GetContent(), "");
}

TEST_F(DocumentTest, TestSetTitle) {
    doc->SetTitle("Test Document");
    EXPECT_EQ(doc->GetTitle(), "Test Document");
}

TEST_F(DocumentTest, TestSetContent) {
    doc->SetContent("This is a test content.");
    EXPECT_EQ(doc->GetContent(), "This is a test content.");
}

TEST_F(DocumentTest, TestClearContent) {
    doc->SetContent("Some content");
    doc->ClearContent();
    EXPECT_EQ(doc->GetContent(), "");
}