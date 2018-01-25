#include <iostream>
#include <memory>
#include <cmath>
#include <vector>

class AVLTree {
private:
  class Node {
  public:
    Node(int key, int value, std::shared_ptr<Node> parent)
        : key_(key), value_(value), parent_(parent), height_(1) {}

    std::shared_ptr<Node> getParent();
    std::shared_ptr<Node> getLeftSon();
    std::shared_ptr<Node> getRightSon();
    int getKey();
    int getValue();
    int getHeight();

    void setParent(std::shared_ptr<Node> node);
    void setLeftSon(std::shared_ptr<Node> node);
    void setRightSon(std::shared_ptr<Node> node);

    void updateHeight();

    ~Node() {}

  private:
    std::shared_ptr<Node> parent_;
    std::shared_ptr<Node> leftSon_;
    std::shared_ptr<Node> rightSon_;
    int key_;
    int value_;
    int height_;
  };

public:
  AVLTree() {}

  void insert(int key, int value);
  bool erase(int key);

  std::pair<int, int> previous(int key);
  std::pair<int, int> successive(int key);

private:
  std::shared_ptr<Node> root;

  std::shared_ptr<Node> find(int value);

  void setParent(std::shared_ptr<Node> node, std::shared_ptr<Node> parent);
  void setSon(std::shared_ptr<Node> node, std::shared_ptr<Node> oldSon,
              std::shared_ptr<Node> newSon);
  void deleteSon(std::shared_ptr<Node> node, std::shared_ptr<Node> son);

  void rebuild(std::shared_ptr<Node> node);

  int getBalance(std::shared_ptr<Node> node);

  std::shared_ptr<Node> smallLeft(std::shared_ptr<Node> node);
  std::shared_ptr<Node> smallRight(std::shared_ptr<Node> node);
  std::shared_ptr<Node> bigLeft(std::shared_ptr<Node> node);
  std::shared_ptr<Node> bigRight(std::shared_ptr<Node> node);
};

std::shared_ptr<AVLTree::Node> AVLTree::Node::getParent() {
  return parent_;
}

std::shared_ptr<AVLTree::Node> AVLTree::Node::getLeftSon() {
  return leftSon_;
}

std::shared_ptr<AVLTree::Node> AVLTree::Node::getRightSon() {
  return rightSon_;
}

int AVLTree::Node::getKey() {
  return key_;
}

int AVLTree::Node::getValue() {
  return value_;
}

int AVLTree::Node::getHeight() {
  return height_;
}

void AVLTree::Node::setParent(std::shared_ptr<AVLTree::Node> node) {
  parent_ = node;
}

void AVLTree::Node::setLeftSon(std::shared_ptr<AVLTree::Node> node) {
  leftSon_ = node;
}

void AVLTree::Node::setRightSon(std::shared_ptr<AVLTree::Node> node) {
  rightSon_ = node;
}

void AVLTree::Node::updateHeight() {
  int h1 = leftSon_ == nullptr ? 0 : leftSon_->getHeight();
  int h2 = rightSon_ == nullptr ? 0 : rightSon_->getHeight();
  height_ = std::max(h1, h2) + 1;
}

void AVLTree::insert(int key, int value) {
  if (root == nullptr) {
    root = std::shared_ptr<Node>(new Node(key, value, nullptr));
  } else {
    std::shared_ptr<Node> node = root;
    while (true) {
      if (node->getKey() < key) {
        if (node->getRightSon() == nullptr) {
          node->setRightSon(std::shared_ptr<Node>(new Node(key, value, node)));
          node->getRightSon()->setParent(node);
          rebuild(node);
          break;
        }
        node = node->getRightSon();
      } else {
        if (node->getLeftSon() == nullptr) {
          node->setLeftSon(std::shared_ptr<Node>(new Node(key, value, node)));
          node->getLeftSon()->setParent(node);
          rebuild(node);
          break;
        }
        node = node->getLeftSon();
      }
    }
  }
}

bool AVLTree::erase(int key) {
  std::shared_ptr<Node> node = find(key);
  if (node != nullptr) {

    if (node->getLeftSon() != nullptr && node->getRightSon() != nullptr) {
      std::shared_ptr<Node> to_swap = node->getLeftSon();
      while (to_swap->getRightSon() != nullptr) {
        to_swap = to_swap->getRightSon();
      }

      std::shared_ptr<Node> temp =
          node == to_swap->getParent() ? to_swap : to_swap->getParent();
      setSon(to_swap->getParent(), to_swap, to_swap->getLeftSon());
      setParent(to_swap->getLeftSon(), to_swap->getParent());
      to_swap->setParent(node->getParent());
      setSon(node->getParent(), node, to_swap);
      to_swap->setRightSon(node->getRightSon());
      setParent(node->getRightSon(), to_swap);
      to_swap->setLeftSon(node->getLeftSon());
      setParent(node->getLeftSon(), to_swap);

      if (root == node) {
        root = to_swap;
      }
      rebuild(temp);
    } else {
      std::shared_ptr<Node> son =
          node->getLeftSon() != nullptr ? node->getLeftSon()
                                        : node->getRightSon();
      if (node->getParent() == nullptr) {
        root = son;
        setParent(son, nullptr);
        return true;
      }
      setParent(son, node->getParent());
      setSon(node->getParent(), node, son);
      node = node->getParent();
      rebuild(node);
    }
    return true;
  }
  return false;
}

std::shared_ptr<AVLTree::Node> AVLTree::find(int key) {
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

void AVLTree::setParent(std::shared_ptr<AVLTree::Node> node,
                        std::shared_ptr<AVLTree::Node> parent) {
  if (node != nullptr) {
    node->setParent(parent);
  }
}

void AVLTree::setSon(std::shared_ptr<AVLTree::Node> node,
                     std::shared_ptr<AVLTree::Node> oldSon,
                     std::shared_ptr<AVLTree::Node> newSon) {
  if (node != nullptr) {
    if (node->getLeftSon() == oldSon) {
      node->setLeftSon(newSon);
    } else if (node->getRightSon() == oldSon) {
      node->setRightSon(newSon);
    } else {
      throw std::runtime_error("Error in function AVLTREE::setSon");
    }
  }
}

void AVLTree::deleteSon(std::shared_ptr<AVLTree::Node> node,
                        std::shared_ptr<AVLTree::Node> son) {
  if (node != nullptr) {
    if (node->getLeftSon() == son) {
      node->setLeftSon(nullptr);
    } else if (node->getRightSon() == son) {
      node->setRightSon(nullptr);
    } else {
      throw std::runtime_error("Error in function AVLTREE::deleteSon");
    }
  }
}

void AVLTree::rebuild(std::shared_ptr<AVLTree::Node> node) {
  while (node != nullptr) {
    node->updateHeight();
    int balance = getBalance(node);
    if (std::abs(balance) <= 1) {
      node = node->getParent();
    } else if (balance == 2) {
      if (getBalance(node->getLeftSon()) == -1) {
        node = bigLeft(node);
      } else {
        node = smallLeft(node);
      }
    } else {
      if (getBalance(node->getRightSon()) == 1) {
        node = bigRight(node);
      } else {
        node = smallRight(node);
      }
    }
  }
}

int AVLTree::getBalance(std::shared_ptr<AVLTree::Node> node) {
  int h1 =
      node->getLeftSon() == nullptr ? 0 : node->getLeftSon()->getHeight();
  int h2 =
      node->getRightSon() == nullptr ? 0 : node->getRightSon()->getHeight();
  return h1 - h2;
}

std::shared_ptr<AVLTree::Node>
AVLTree::smallLeft(std::shared_ptr<AVLTree::Node> node) {
  std::shared_ptr<Node> left_son = node->getLeftSon();
  left_son->setParent(node->getParent());
  setSon(node->getParent(), node, left_son);
  node->setLeftSon(left_son->getRightSon());
  setParent(node->getLeftSon(), node);
  left_son->setRightSon(node);
  node->setParent(left_son);
  node->updateHeight();
  left_son->updateHeight();
  if (root == node) {
    root = left_son;
  }
  return left_son->getParent();
}

std::shared_ptr<AVLTree::Node>
AVLTree::smallRight(std::shared_ptr<AVLTree::Node> node) {
  std::shared_ptr<Node> right_son = node->getRightSon();
  right_son->setParent(node->getParent());
  setSon(node->getParent(), node, right_son);
  node->setRightSon(right_son->getLeftSon());
  setParent(node->getRightSon(), node);
  right_son->setLeftSon(node);
  node->setParent(right_son);
  node->updateHeight();
  right_son->updateHeight();
  if (root == node) {
    root = right_son;
  }
  return right_son->getParent();
}

std::shared_ptr<AVLTree::Node>
AVLTree::bigLeft(std::shared_ptr<AVLTree::Node> node) {
  std::shared_ptr<Node> son = node->getLeftSon();
  std::shared_ptr<Node> grandson = son->getRightSon();
  grandson->setParent(node->getParent());
  setSon(node->getParent(), node, grandson);
  node->setParent(grandson);
  son->setParent(grandson);
  son->setRightSon(grandson->getLeftSon());
  node->setLeftSon(grandson->getRightSon());
  grandson->setLeftSon(son);
  grandson->setRightSon(node);
  setParent(son->getRightSon(), son);
  setParent(node->getLeftSon(), node);
  node->updateHeight();
  son->updateHeight();
  grandson->updateHeight();
  if (root == node) {
    root = grandson;
  }
  return grandson->getParent();
}

std::shared_ptr<AVLTree::Node>
AVLTree::bigRight(std::shared_ptr<AVLTree::Node> node) {
  std::shared_ptr<Node> son = node->getRightSon();
  std::shared_ptr<Node> grandson = son->getLeftSon();
  grandson->setParent(node->getParent());
  setSon(node->getParent(), node, grandson);
  node->setParent(grandson);
  son->setParent(grandson);
  node->setRightSon(grandson->getLeftSon());
  son->setLeftSon(grandson->getRightSon());
  grandson->setLeftSon(node);
  grandson->setRightSon(son);
  setParent(node->getRightSon(), node);
  setParent(son->getLeftSon(), son);
  node->updateHeight();
  son->updateHeight();
  grandson->updateHeight();
  if (root == node) {
    root = grandson;
  }
  return grandson->getParent();
}

std::pair<int, int> AVLTree::previous(int key) {
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

std::pair<int, int> AVLTree::successive(int key) {
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

int main() {
  int n;
  std::cin >> n;
  std::vector<int> group_indexes;
  AVLTree avl_tree;
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