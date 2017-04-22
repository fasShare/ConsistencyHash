#include "HashNode.h"

HashNode::HashNode(MD5 *md5, std::string initName, int nameNum) :
    keys_(),
    initName_(initName),
    nameNum_(nameNum),
    md5_(md5),
    mappedCount_(0) {

    std::string virName;

    for (int i = 0; i < nameNum_; i++) {
        srandom(random());
        virName = initName_ + "HashNode" + std::to_string(i) + std::to_string(random());
        md5_->GenerateMD5(virName.c_str(), virName.length());
        keys_.push_back(md5_->ToULong32());
    }
}

const std::vector<HashNode::KeyType>& HashNode::getNodeKeys() const {
    return this->keys_;
}

std::string HashNode::getInitName() const {
    return initName_;
}

void HashNode::increaseMappedCount() {
    this->mappedCount_++;
}

unsigned long long HashNode::getMappedCount() const {
    return this->mappedCount_;
}
