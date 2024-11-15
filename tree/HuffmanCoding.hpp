/**
 * @file HuffmanCoding.hpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 哈夫曼编码
 * @version 1.0
 * @date 2024-11-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

class HuffmanCoding {
 public:
  struct HuffmanTree {
    int freq_{};
    char ch_{};
    HuffmanTree* left_{nullptr};
    HuffmanTree* right_{nullptr};

    struct Compare {
      bool operator()(const HuffmanTree* a, const HuffmanTree* b) const {
        return a->freq_ > b->freq_;
      }
    };

    HuffmanTree() = default;
    HuffmanTree(char ch, int freq, HuffmanTree* left = nullptr, HuffmanTree* right = nullptr)
        : ch_(ch), freq_(freq), left_(left), right_(right) {}
    ~HuffmanTree() {
      delete left_;
      delete right_;
    }
  };

  using Code_t = std::vector<bool>;
  using CodeTable = std::map<char, Code_t>;
  using FreqTable = std::vector<std::pair<char, int>>;

 private:
  void buildTree();

  void buildCodeTable();

  void mkFreqTable(const std::string& text);

  Code_t encode(const std::string& text);

 public:
  HuffmanCoding() = default;
  ~HuffmanCoding() = default;

  void printCodeTable();

  std::string serialize(const Code_t& bit_vec);

  Code_t deserialize(const std::string& packed);

  std::string decode(const Code_t& bit_vec);

  void hexDump(const std::string& packed);

  inline Code_t operator()(const std::string& text) {
    mkFreqTable(text);
    buildTree();
    buildCodeTable();
    return encode(text);
  }

 private:
  std::unique_ptr<HuffmanTree> huffman_tree_;
  std::unique_ptr<FreqTable> freq_table_;
  std::unique_ptr<CodeTable> code_table_;
};

// 建树
void HuffmanCoding::buildTree() {
  std::priority_queue<HuffmanTree*, std::vector<HuffmanTree*>, HuffmanTree::Compare> min_heap;
  for (const auto& p : *freq_table_) {
    HuffmanTree* tmp = new HuffmanTree(p.first, p.second);
    min_heap.push(tmp);
  }

  HuffmanTree* root;
  while (min_heap.size() > 1) {
    HuffmanTree *l, *r;
    l = min_heap.top();
    min_heap.pop();
    r = min_heap.top();
    min_heap.pop();
    root = new HuffmanTree(0, l->freq_ + r->freq_, l, r);
    min_heap.push(root);
  }
  huffman_tree_.reset(root);
}

// 构建编码表
void HuffmanCoding::buildCodeTable() {
  CodeTable code_table;
  std::deque<std::pair<HuffmanTree*, Code_t>> q;
  q.push_back(std::make_pair(huffman_tree_.get(), Code_t()));
  while (!q.empty()) {
    HuffmanTree* node = q.front().first;
    Code_t code = q.front().second;
    HuffmanTree* lc = node->left_;
    HuffmanTree* rc = node->right_;
    q.pop_front();
    if (lc) {  // 若左子树存在，则右子树也必然存在，反之同理
      Code_t t(code);
      code.push_back(0);
      q.push_back(std::make_pair(lc, code));
      t.push_back(1);
      q.push_back(std::make_pair(rc, t));
    } else {
      code_table.emplace(node->ch_, code);
    }
  }
  code_table_ = std::make_unique<CodeTable>(code_table);
}

// 序列化
std::string HuffmanCoding::serialize(const Code_t& bit_vec) {
  std::string result{};

  // 控制台只能显示可打印的字符，对于不可打印的字符（如控制字符或非 ASCII
  // 字符），会显示为乱码或特殊符号。 因此控制台显示的字符长度很可能小于实际长度(result.size())
  const unsigned len = bit_vec.size();
  const unsigned redu = len & 7;  // 记录冗余位，表示最后一个字节中未填满的位数
  result += static_cast<char>(
      redu);  // 将悬挂位数作为第一个字节写入结果字符串。这是为了在解码时知道最后一个字节中有多少位是有效的。

  char byte = 0;
  for (unsigned i = 0; i < len; i++) {
    unsigned boff = i & 7;  // 等同于 i % 8
    byte |= bit_vec[i] << boff;
    if (boff == 7) {
      result += byte;
      byte = 0;
    }
  }
  if (redu) {
    result += byte;
  }

  return result;
}

// 反序列化
HuffmanCoding::Code_t HuffmanCoding::deserialize(const std::string& packed) {
  Code_t result{};
  const unsigned len = packed.length();

  unsigned redu = static_cast<unsigned>(packed[0]);
  for (unsigned p = 1; p < len;
       p++) {  // 第一个字符用作记录最后一个字节的有效位数，因此从第二个字符开始遍历
    for (int i = 0; i < 8; i++) {
      result.emplace_back((packed[p] >> i) & 1);
    }
  }

  if (redu) {
    for (unsigned i = 0; i < (8 - redu); i++) {
      result.pop_back();
    }
  }
  return result;
}

// 打印内存视图
void HuffmanCoding::hexDump(const std::string& packed) {
  const unsigned char* bytes = reinterpret_cast<const unsigned char*>(packed.c_str());
  int nbytes = packed.size();
  int i, j;

  for (i = 0; i < nbytes; i += 16) {
    printf("%06x: ", i);
    for (j = 0; j < 16; j++) {
      if (i + j < nbytes) {
        printf("%02x ", bytes[i + j]);
      } else {
        printf("   ");
      }
    }
    printf(" ");
    for (j = 0; j < 16; j++)
      if (i + j < nbytes) printf("%c", isprint(bytes[i + j]) ? bytes[i + j] : '.');
    printf("\n");
  }
}

void HuffmanCoding::printCodeTable() {
  if (code_table_) {
    std::cout << "Code Table:\n";
    for (const auto& [ch, code_t] : *code_table_) {
      std::cout << "  (" << ch << ", ";
      for (const int i : code_t) {
        std::cout << i;
      }
      std::cout << ")\n";
    }
  } else {
    std::cout << "no code-table\n";
  }
}

// 制作字符频率表
void HuffmanCoding::mkFreqTable(const std::string& text) {
  std::map<char, int> map_char_freq;
  FreqTable freq_table;
  for (const char ch : text) {
    if (map_char_freq.find(ch) == map_char_freq.end()) {
      map_char_freq.emplace(ch, 1);
    } else {
      map_char_freq.at(ch)++;
    }
  }
  for (const auto [ch, freq] : map_char_freq) {
    freq_table.emplace_back(ch, freq);
  }
  freq_table_ = std::make_unique<FreqTable>(freq_table);
}

// 编码
HuffmanCoding::Code_t HuffmanCoding::encode(const std::string& text) {
  Code_t code;
  const int len = text.length();
  for (const char ch : text) {
    Code_t t = code_table_->at(ch);
    code.insert(code.end(), t.begin(), t.end());
  }
  return code;
}

// 解码
std::string HuffmanCoding::decode(const Code_t& bit_vec) {
  std::string result{};
  HuffmanTree* node = huffman_tree_.get();
  for (const unsigned bit : bit_vec) {
    node = bit ? node->right_ : node->left_;
    if (!node->left_) {
      result += node->ch_;
      node = huffman_tree_.get();
    }
  }
  return result;
}
