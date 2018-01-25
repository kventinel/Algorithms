#include <iostream>
#include <memory>
#include <vector>

class splay_tree {
public:
  splay_tree() {}

  bool can_leave(std::pair<int, int> room);

  void insert(std::pair<int, int> room);
  void erase(int first_room);

  ~splay_tree() {
  }

private:
  struct node {
      std::shared_ptr<node> parent = nullptr;
      std::shared_ptr<node> left_son = nullptr;
      std::shared_ptr<node> right_son = nullptr;

      std::pair<int, int> room;

      ~node() {}
  };

  splay_tree(std::shared_ptr<node> another_root) {
    root = another_root;
  }

  std::shared_ptr<node> root = nullptr;

  void set_parent(std::shared_ptr<node> this_node, std::shared_ptr<node> parent);

  void zig(std::shared_ptr<node> this_node);
  void zag(std::shared_ptr<node> this_node);
  void zig_zig(std::shared_ptr<node> this_node);
  void zig_zag(std::shared_ptr<node> this_node);
  void zag_zig(std::shared_ptr<node> this_node);
  void zag_zag(std::shared_ptr<node> this_node);

  void splay(std::shared_ptr<node> this_node);

  std::shared_ptr<splay_tree> split(bool without_root, int key);
  void merge(std::shared_ptr<splay_tree> right_tree);

  void find(int first_room);

  bool cross(std::pair<int, int> room1, std::pair<int, int> room2);
};

void splay_tree::set_parent(std::shared_ptr<splay_tree::node> this_node, std::shared_ptr<splay_tree::node> parent) {
  if (this_node != nullptr) {
    this_node->parent = parent;
  }
}

void splay_tree::zig(std::shared_ptr<splay_tree::node> this_node) {
  std::shared_ptr<node> x = this_node;
  std::shared_ptr<node> y = x->parent;
  std::shared_ptr<node> b = x->right_son;
  set_parent(x, y->parent);
  set_parent(y, x);
  set_parent(b, y);
  x->right_son = y;
  y->left_son = b;
  if (x->parent != nullptr) {
    if (x->parent->left_son == y) {
      x->parent->left_son = x;
    } else {
      x->parent->right_son = x;
    }
  }
}

void splay_tree::zag(std::shared_ptr<splay_tree::node> this_node) {
  std::shared_ptr<node> x = this_node;
  std::shared_ptr<node> y = x->parent;
  std::shared_ptr<node> b = x->left_son;
  set_parent(x, y->parent);
  set_parent(y, x);
  set_parent(b, y);
  x->left_son = y;
  y->right_son = b;
  if (x->parent != nullptr) {
    if (x->parent->left_son == y) {
      x->parent->left_son = x;
    } else {
      x->parent->right_son = x;
    }
  }
}

void splay_tree::zig_zig(std::shared_ptr<splay_tree::node> this_node) {
  std::shared_ptr<node> x = this_node;
  std::shared_ptr<node> y = x->parent;
  std::shared_ptr<node> z = y->parent;
  std::shared_ptr<node> b = x->right_son;
  std::shared_ptr<node> c = y->right_son;
  set_parent(x, z->parent);
  set_parent(y, x);
  set_parent(z, y);
  set_parent(b, y);
  set_parent(c, z);
  x->right_son = y;
  y->left_son = b;
  y->right_son = z;
  z->left_son = c;
  if (x->parent != nullptr) {
    if (x->parent->left_son == z) {
      x->parent->left_son = x;
    } else {
      x->parent->right_son = x;
    }
  }
}

void splay_tree::zig_zag(std::shared_ptr<splay_tree::node> this_node) {
  std::shared_ptr<node> x = this_node;
  std::shared_ptr<node> y = x->parent;
  std::shared_ptr<node> z = y->parent;
  std::shared_ptr<node> b = x->left_son;
  std::shared_ptr<node> c = x->right_son;
  set_parent(x, z->parent);
  set_parent(y, x);
  set_parent(z, x);
  set_parent(b, y);
  set_parent(c, z);
  x->left_son = y;
  x->right_son = z;
  y->right_son = b;
  z->left_son = c;
  if (x->parent != nullptr) {
    if (x->parent->left_son == z) {
      x->parent->left_son = x;
    } else {
      x->parent->right_son = x;
    }
  }
}

void splay_tree::zag_zig(std::shared_ptr<splay_tree::node> this_node) {
  std::shared_ptr<node> x = this_node;
  std::shared_ptr<node> y = x->parent;
  std::shared_ptr<node> z = y->parent;
  std::shared_ptr<node> b = x->left_son;
  std::shared_ptr<node> c = x->right_son;
  set_parent(x, z->parent);
  set_parent(y, x);
  set_parent(z, x);
  set_parent(b, z);
  set_parent(c, y);
  x->left_son = z;
  x->right_son = y;
  y->left_son = c;
  z->right_son = b;
  if (x->parent != nullptr) {
    if (x->parent->left_son == z) {
      x->parent->left_son = x;
    } else {
      x->parent->right_son = x;
    }
  }
}

void splay_tree::zag_zag(std::shared_ptr<splay_tree::node> this_node) {
  std::shared_ptr<node> x = this_node;
  std::shared_ptr<node> y = x->parent;
  std::shared_ptr<node> z = y->parent;
  std::shared_ptr<node> b = y->left_son;
  std::shared_ptr<node> c = x->left_son;
  set_parent(x, z->parent);
  set_parent(y, x);
  set_parent(z, y);
  set_parent(b, z);
  set_parent(c, y);
  x->left_son = y;
  y->left_son = z;
  y->right_son = c;
  z->right_son = b;
  if (x->parent != nullptr) {
    if (x->parent->left_son == z) {
      x->parent->left_son = x;
    } else {
      x->parent->right_son = x;
    }
  }
}

void splay_tree::splay(std::shared_ptr<splay_tree::node> this_node) {
  while (this_node != nullptr && this_node->parent != nullptr) {
    if (this_node->parent->parent == nullptr) {
      if (this_node->parent->left_son == this_node) {
        zig(this_node);
      } else {
        zag(this_node);
      }
    } else if (this_node->parent->parent->left_son == this_node->parent) {
      if (this_node->parent->left_son == this_node) {
        zig_zig(this_node);
      } else {
        zig_zag(this_node);
      }
    } else {
      if (this_node->parent->left_son == this_node) {
        zag_zig(this_node);
      } else {
        zag_zag(this_node);
      }
    }
  }
  root = this_node;
}

std::shared_ptr<splay_tree> splay_tree::split(bool without_root, int key = 0) {
  if (root == nullptr) {
    return std::shared_ptr<splay_tree> (new splay_tree);
  }
  if (without_root) {
    std::shared_ptr<splay_tree> right_tree(new splay_tree(root->right_son));
    std::shared_ptr<node> left_tree = root->left_son;
    set_parent(right_tree->root, nullptr);
    set_parent(left_tree, nullptr);
    root->left_son = nullptr;
    root->right_son = nullptr;
    root = left_tree;
    return right_tree;
  }
  if (key < root->room.first) {
    std::shared_ptr<splay_tree> right_tree(new splay_tree(root));
    std::shared_ptr<node> left_tree = root->left_son;
    set_parent(left_tree, nullptr);
    root = left_tree;
    right_tree->root->left_son = nullptr;
    return right_tree;
  }
  std::shared_ptr<splay_tree> right_tree(new splay_tree(root->right_son));
  root->right_son = nullptr;
  set_parent(right_tree->root, nullptr);
  return right_tree;
}

void splay_tree::merge(std::shared_ptr<splay_tree> right_tree) {
  if (right_tree->root != nullptr) {
    while (right_tree->root->left_son != nullptr) {
      right_tree->root = right_tree->root->left_son;
    }
    right_tree->splay(right_tree->root);
    right_tree->root->left_son = root;
    set_parent(root, right_tree->root);
    root = right_tree->root;
  }
}

bool splay_tree::can_leave(std::pair<int, int> room) {
  if (root == nullptr) {
    return true;
  }
  find(room.first);
  std::shared_ptr<node> this_node = root;
  if (cross(this_node->room, room)) {
    return false;
  }
  if (this_node->room.first < room.first) {
    if (this_node->right_son != nullptr) {
      this_node = this_node->right_son;
      while (this_node->left_son != nullptr) {
        this_node = this_node->left_son;
      }
    }
  } else {
    if (this_node->left_son != nullptr) {
      this_node = this_node->left_son;
      while (this_node->right_son != nullptr) {
        this_node = this_node->right_son;
      }
    }
  }
  splay(this_node);
  return !cross(this_node->room, room);
}

void splay_tree::insert(std::pair<int, int> room) {
  std::shared_ptr<splay_tree> right_tree = split(false, room.first);
  std::shared_ptr<node> new_node(new node());
  new_node->room = room;
  new_node->left_son = root;
  new_node->right_son = right_tree->root;
  set_parent(root, new_node);
  set_parent(right_tree->root, new_node);
  root = new_node;
}

void splay_tree::erase(int first_room) {
  find(first_room);
  std::shared_ptr<splay_tree> right_tree = split(true);
  merge(right_tree);
}

void splay_tree::find(int first_room) {
  std::shared_ptr<node> this_node = root;
  while (this_node != nullptr) {
    if (first_room < this_node->room.first) {
      if (this_node->left_son != nullptr) {
        this_node = this_node->left_son;
      } else {
        splay(this_node);
        break;
      }
    } else if (first_room > this_node->room.first) {
      if (this_node->right_son != nullptr) {
        this_node = this_node->right_son;
      } else {
        splay(this_node);
        break;
      }
    } else {
      splay(this_node);
      break;
    }
  }
}

bool splay_tree::cross(std::pair<int, int> room1, std::pair<int, int> room2) {
  if (room1.first <= room2.first && room1.first + room1.second > room2.first) {
    return true;
  }
  return room2.first <= room1.first && room2.first + room2.second > room1.first;
}

int main() {
  int t;
  std::cin >> t;
  std::vector<std::pair<int, int>> requests;
  std::vector<int> answer;
  splay_tree tree;
  while (t > 0) {
    --t;
    int type;
    std::cin >> type;
    if (type == 1) {
      std::pair<int, int> room;
      std::cin >> room.first >> room.second;
      bool good = tree.can_leave(room);
      if (good) {
        tree.insert(room);
        requests.push_back(std::pair<int, int>(1, room.first));
        answer.push_back(1);
      } else {
        requests.push_back(std::pair<int, int>(0, room.first));
        answer.push_back(0);
      }
    } else {
      int request;
      std::cin >> request;
      if (requests[request].first == 1) {
        tree.erase(requests[request].second);
        requests[request].first = 2;
        answer.push_back(1);
      } else {
        answer.push_back(0);
      }
    }
  }
  for (size_t i = 0; i < answer.size(); ++i) {
    std::cout << answer[i];
  }
  std::cout << std::endl;
  return 0;
}