#include "ConsistencyHash.h"
#include <iostream>

ConsistencyHash::ConsistencyHash(int virtualNodeNum) :
    virtualNodeNum_(virtualNodeNum),
    md5_(),
    nodes_(),
    hashMap_() {

}

bool ConsistencyHash::addHashNodesFromString(std::string nodeName) {

    auto iter = nodes_.find(nodeName);
    if (iter != nodes_.end()) {
        return false;
    }

    std::shared_ptr<HashNode> node = std::make_shared<HashNode>(&md5_, nodeName, virtualNodeNum_);
    nodes_[nodeName] = node;

    std::vector<HashNode::KeyType> nodeKeys = node->getNodeKeys();

    for (auto iter = nodeKeys.begin(); iter != nodeKeys.end(); ++iter) {
        hashMap_.insert({
            *iter, node
                        });
    }

    return true;
}

bool ConsistencyHash::deleteHashNodesFromString(std::string nodeName) {
    auto iter = nodes_.find(nodeName);
    if (iter == nodes_.end()) {
        return true;
    }
    std::vector<HashNode::KeyType> nodeKeys = iter->second->getNodeKeys();

    for (auto iter = nodeKeys.begin(); iter != nodeKeys.end(); ++iter) {
        hashMap_.erase(*iter);
    }

    return true;
}

ConsistencyHash::MappingNodeIter
ConsistencyHash::getMappingNodeFromKey(HashNode::KeyType key) {
    auto iter = hashMap_.upper_bound(key);
    if (iter == hashMap_.end()) {
        iter = hashMap_.begin();
    }

    iter->second->increaseMappedCount();
    return iter;
}

void ConsistencyHash::ShowNodeMsg() {
    for (auto iter = hashMap_.begin(); iter != hashMap_.end(); ++iter) {
        std::cout << iter->second->getInitName() << std::endl;
    }
}

void ConsistencyHash::ShowMappingStatisticMsg() {
    for (auto iter = nodes_.begin(); iter != nodes_.end(); ++iter) {
        std::cout << iter->second->getInitName() << "  " << iter->second->getMappedCount() << endl;
    }
}
