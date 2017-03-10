#include <iostream>
#include <memory>
#include <cmath>
#include <vector>

class RBTree {
private:
  class Node {
  public:
    Node(int key, int value, std::shared_ptr<Node> parent)
        : key_(key), value_(value), parent_(parent), black_(false) {}

    std::shared_ptr<Node> getParent();
    std::shared_ptr<Node> getLeftSon();
    std::shared_ptr<Node> getRightSon();
    int getKey();
    int getValue();

    void setParent(std::shared_ptr<Node> node);
    void setLeftSon(std::shared_ptr<Node> node);
    void setRightSon(std::shared_ptr<Node> node);

    bool isRed();
    bool isBlack();
    void setRed();
    void setBlack();
    void setColor(std::shared_ptr<Node> node);

    ~Node() {}

  private:
    std::shared_ptr<Node> parent_;
    std::shared_ptr<Node> leftSon_;
    std::shared_ptr<Node> rightSon_;
    int key_;
    int value_;
    bool black_;
  };

public:
  RBTree() {}

  void insert(int key, int value);
  bool erase(int key);

  std::pair<int, int> previous(int key);
  std::pair<int, int> successive(int key);

private:
  std::shared_ptr<Node> root;

  std::shared_ptr<Node> find(int value);

  void setParent(std::shared_ptr<Node> node, std::shared_ptr<Node> parent);
  void setLeftSon(std::shared_ptr<Node> node, std::shared_ptr<Node> son);
  void setRightSon(std::shared_ptr<Node> node, std::shared_ptr<Node> son);
  void setSon(std::shared_ptr<Node> node, std::shared_ptr<Node> oldSon,
              std::shared_ptr<Node> newSon);

  void insertRebuild(std::shared_ptr<Node> node);
  void eraseRebuild(std::shared_ptr<Node> node);
};

bool RBTree::Node::isRed() {
  return !black_;
}

bool RBTree::Node::isBlack() {
  return black_;
}

void RBTree::Node::setRed() {
  black_ = false;
}

void RBTree::Node::setBlack() {
  black_ = true;
}

std::shared_ptr<RBTree::Node> RBTree::Node::getParent() {
  return parent_;
}

std::shared_ptr<RBTree::Node> RBTree::Node::getLeftSon() {
  return leftSon_;
}

std::shared_ptr<RBTree::Node> RBTree::Node::getRightSon() {
  return rightSon_;
}

int RBTree::Node::getKey() {
  return key_;
}

int RBTree::Node::getValue() {
  return value_;
}

void RBTree::Node::setParent(std::shared_ptr<RBTree::Node> node) {
  parent_ = node;
}

void RBTree::Node::setLeftSon(std::shared_ptr<RBTree::Node> node) {
  leftSon_ = node;
}

void RBTree::Node::setRightSon(std::shared_ptr<RBTree::Node> node) {
  rightSon_ = node;
}

void RBTree::Node::setColor(std::shared_ptr<RBTree::Node> node) {
  if (node != nullptr) {
    black_ = node->isBlack();
  }
}

void RBTree::insert(int key, int value) {
  if (root == nullptr) {
    root = std::shared_ptr<Node>(new Node(key, value, nullptr));
  } else {
    std::shared_ptr<Node> node = root;
    while (true) {
      if (node->getKey() < key) {
        if (node->getRightSon() == nullptr) {
          node->setRightSon(std::shared_ptr<Node>(new Node(key, value, node)));
          node->getRightSon()->setParent(node);
          insertRebuild(node->getRightSon());
          break;
        }
        node = node->getRightSon();
      } else {
        if (node->getLeftSon() == nullptr) {
          node->setLeftSon(std::shared_ptr<Node>(new Node(key, value, node)));
          node->getLeftSon()->setParent(node);
          insertRebuild(node->getLeftSon());
          break;
        }
        node = node->getLeftSon();
      }
    }
  }
}

bool RBTree::erase(int key) {
  std::shared_ptr<Node> node = find(key);
  if (node != nullptr) {
    if (node->getLeftSon() != nullptr && node->getRightSon() != nullptr) {
      std::shared_ptr<Node> to_swap = node->getLeftSon();
      while (to_swap->getRightSon() != nullptr) {
        to_swap = to_swap->getRightSon();
      }
      std::shared_ptr<Node> son = to_swap->getLeftSon();
      if (to_swap->isBlack()) {
        if (son != nullptr && son->isRed()) {
          son->setBlack();
        } else {
          eraseRebuild(to_swap);
        }
      }
      std::shared_ptr<Node> temp =
          node == to_swap->getParent() ? to_swap : to_swap->getParent();
      setSon(to_swap->getParent(), to_swap, son);
      setSon(node->getParent(), node, to_swap);
      setLeftSon(to_swap, node->getLeftSon());
      setRightSon(to_swap, node->getRightSon());
      if (root == node) {
        root = to_swap;
      }
      to_swap->setColor(node);
    } else {
      std::shared_ptr<Node> son =
          node->getLeftSon() != nullptr ? node->getLeftSon()
                                        : node->getRightSon();
      if (node->getParent() == nullptr) {
        root = son;
        setParent(son, nullptr);
        return true;
      }
      if (node->isBlack()) {
        if (son != nullptr && son->isRed()) {
          son->setBlack();
        } else {
          eraseRebuild(node);
        }
      }
      setSon(node->getParent(), node, son);
      node = node->getParent();
    }
    return true;
  }
  return false;
}

std::shared_ptr<RBTree::Node> RBTree::find(int key) {
  std::shared_ptr<Node> node = root;
  while (node != nullptr && node->getKey() != key) {
    if (node->getKey() > key) {
      node = node->getLeftSon();
    } else {
      node = node->getRightSon();
    }
  }
  return node;
}

void RBTree::setParent(std::shared_ptr<RBTree::Node> node,
                       std::shared_ptr<RBTree::Node> parent) {
  if (node != nullptr) {
    node->setParent(parent);
  }
}

void RBTree::setSon(std::shared_ptr<RBTree::Node> node,
                    std::shared_ptr<RBTree::Node> oldSon,
                    std::shared_ptr<RBTree::Node> newSon) {
  if (node != nullptr) {
    if (node->getLeftSon() == oldSon) {
      node->setLeftSon(newSon);
    } else if (node->getRightSon() == oldSon) {
      node->setRightSon(newSon);
    } else {
      throw std::runtime_error("Error in function AVLTREE::setSon");
    }
  }
  if (newSon != nullptr) {
    newSon->setParent(node);
  }
}

std::pair<int, int> RBTree::previous(int key) {
  std::shared_ptr<Node> node = root;
  if (node == nullptr) {
    return std::make_pair(-1, -1);
  }
  while (true) {
    if (node->getKey() == key) {
      return std::make_pair(node->getKey(), node->getValue());
    }
    if (node->getKey() < key) {
      if (node->getRightSon() != nullptr) {
        node = node->getRightSon();
      } else {
        return std::make_pair(node->getKey(), node->getValue());
      }
    } else {
      if (node->getLeftSon() != nullptr) {
        node = node->getLeftSon();
      } else {
        std::shared_ptr<Node> parent = node->getParent();
        while (parent != nullptr) {
          if (parent->getRightSon() == node) {
            return std::make_pair(parent->getKey(), parent->getValue());
          } else {
            node = parent;
            parent = node->getParent();
          }
        }
        return std::make_pair(-1, -1);
      }
    }
  }
}

std::pair<int, int> RBTree::successive(int key) {
  std::shared_ptr<Node> node = root;
  if (node == nullptr) {
    return std::make_pair(-1, -1);
  }
  while (true) {
    if (node->getKey() == key) {
      return std::make_pair(node->getKey(), node->getValue());
    }
    if (node->getKey() > key) {
      if (node->getLeftSon() != nullptr) {
        node = node->getLeftSon();
      } else {
        return std::make_pair(node->getKey(), node->getValue());
      }
    } else {
      if (node->getRightSon() != nullptr) {
        node = node->getRightSon();
      } else {
        std::shared_ptr<Node> parent = node->getParent();
        while (parent != nullptr) {
          if (parent->getLeftSon() == node) {
            return std::make_pair(parent->getKey(), parent->getValue());
          } else {
            node = parent;
            parent = node->getParent();
          }
        }
        return std::make_pair(-1, -1);
      }
    }
  }
}

void RBTree::insertRebuild(std::shared_ptr<RBTree::Node> node_) {
  std::shared_ptr<Node> node = node_;
  while (true) {
    std::shared_ptr<Node> parent = node->getParent();
    if (parent == nullptr || parent->isBlack()) {
      return;
    }
    if (parent == root) {
      parent->setBlack();
      return;
    }
    std::shared_ptr<Node> grandparent = parent->getParent();
    std::shared_ptr<Node> uncle =
        parent == grandparent->getLeftSon() ? grandparent->getRightSon()
                                            : grandparent->getLeftSon();
    if (uncle != nullptr && uncle->isRed()) {
      uncle->setBlack();
      parent->setBlack();
      grandparent->setRed();
      node = grandparent;
      continue;
    }
    if (parent == grandparent->getLeftSon()) {
      if (node == parent->getLeftSon()) {
        setSon(grandparent->getParent(), grandparent, parent);
        setLeftSon(grandparent, parent->getRightSon());
        setRightSon(parent, grandparent);
        grandparent->setRed();
        parent->setBlack();
        if (grandparent == root) {
          root = parent;
        }
      } else {
        setSon(grandparent->getParent(), grandparent, node);
        setRightSon(parent, node->getLeftSon());
        setLeftSon(grandparent, node->getRightSon());
        setLeftSon(node, parent);
        setRightSon(node, grandparent);
        node->setBlack();
        grandparent->setRed();
        if (grandparent == root) {
          root = node;
        }
      }
    } else {
      if (node == parent->getLeftSon()) {
        setSon(grandparent->getParent(), grandparent, node);
        setRightSon(grandparent, node->getLeftSon());
        setLeftSon(parent, node->getRightSon());
        setLeftSon(node, grandparent);
        setRightSon(node, parent);
        node->setBlack();
        grandparent->setRed();
        if (grandparent == root) {
          root = node;
        }
      } else {
        setSon(grandparent->getParent(), grandparent, parent);
        setRightSon(grandparent, parent->getLeftSon());
        setLeftSon(parent, grandparent);
        grandparent->setRed();
        parent->setBlack();
        if (grandparent == root) {
          root = parent;
        }
      }
    }
    return;
  }
}

void RBTree::eraseRebuild(std::shared_ptr<RBTree::Node> node) {
  while (true) {
    if (node == root) {
      return;
    }
    std::shared_ptr<Node> parent = node->getParent();
    bool left = (node == parent->getLeftSon());
    std::shared_ptr<Node> brother = left ? parent->getRightSon()
                                         : parent->getLeftSon();
    if (brother->isRed()) {
      setSon(parent->getParent(), parent, brother);
      brother->setBlack();
      parent->setRed();
      if (parent == root) {
        root = brother;
      }
      if (left) {
        setRightSon(parent, brother->getLeftSon());
        setLeftSon(brother, parent);
      } else {
        setLeftSon(parent, brother->getRightSon());
        setRightSon(brother, parent);
      }
      continue;
    }
    bool left_son_black =
        brother->getLeftSon() != nullptr ? brother->getLeftSon()->isBlack()
                                         : true;
    bool right_son_black =
        brother->getRightSon() != nullptr ? brother->getRightSon()->isBlack()
                                          : true;
    if (right_son_black && left_son_black) {
      brother->setRed();
      if (parent->isBlack()) {
        node = parent;
        continue;
      } else {
        parent->setBlack();
        return;
      }
    }
    if (left && right_son_black) {
      std::shared_ptr<Node> son = brother->getLeftSon();
      setRightSon(parent, son);
      setLeftSon(brother, son->getRightSon());
      setRightSon(son, brother);
    }
    if (!left && left_son_black) {
      std::shared_ptr<Node> son = brother->getRightSon();
      setLeftSon(parent, son);
      setRightSon(brother, son->getLeftSon());
      setLeftSon(son, brother);
    }
    brother = left ? parent->getRightSon() : parent->getLeftSon();
    setSon(parent->getParent(), parent, brother);
    brother->setColor(parent);
    parent->setBlack();
    if (left) {
      brother->getRightSon()->setBlack();
      setRightSon(parent, brother->getLeftSon());
      setLeftSon(brother, parent);
    } else {
      brother->getLeftSon()->setBlack();
      setLeftSon(parent, brother->getRightSon());
      setRightSon(brother, parent);
    }
    if (root == parent) {
      root = brother;
    }
    return;
  }
}

void RBTree::setLeftSon(std::shared_ptr<RBTree::Node> node,
                        std::shared_ptr<RBTree::Node> son) {
  if (node != nullptr) {
    node->setLeftSon(son);
  }
  if (son != nullptr) {
    son->setParent(node);
  }
}

void RBTree::setRightSon(std::shared_ptr<RBTree::Node> node,
                         std::shared_ptr<RBTree::Node> son) {
  if (node != nullptr) {
    node->setRightSon(son);
  }
  if (son != nullptr) {
    son->setParent(node);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> group_indexes;
  RBTree avl_tree;
  std::string answer;
  while (n-- > 0) {
    int t;
    std::cin >> t;
    if (t == 1) {
      int l, k;
      std::cin >> l >> k;
      std::pair<int, int> collision = avl_tree.previous(l);
      if (collision.first + collision.second > l) {
        group_indexes.push_back(-1);
        answer += '0';
      } else {
        collision = avl_tree.successive(l);
        if (collision.first < l + k && collision.first >= l) {
          group_indexes.push_back(-1);
          answer += '0';
        } else {
          group_indexes.push_back(l);
          avl_tree.insert(l, k);
          answer += '1';
        }
      }
    } else {
      int i;
      std::cin >> i;
      if (i >= group_indexes.size() || group_indexes[i] == -1) {
        answer += '0';
      } else {
        avl_tree.erase(group_indexes[i]);
        group_indexes[i] = -1;
        answer += '1';
      }
    }
  }
  std::cout << answer << std::endl;
  return 0;
}