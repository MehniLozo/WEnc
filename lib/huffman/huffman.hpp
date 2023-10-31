#ifndef WENC_HUFFMANTREE_H
#define WENC_HUFFMANTREE_H
#include <vector>
#include <memory>

namespace wenc {
    class huffmanTree_t {
        public:
            using huffCode_t = std::vector<bool>;
            using huffPoint_t = std::vector<std::size_t>;

            struct huffData final{
                huffCode_t huffCode;
                huffPoint_t huffPoint;

                huffData() = default;
                huffData(const huffCode_t &_huffCode,
                        const huffPoint_t &_huffPoint):
                        huffCode(_huffCode), huffPoint(_huffPoint){}
            };
        private:
            class node_huff {
                public:
                    const std::size_t frequency;

                    virtual ~node_huff() = default;
                protected:
                    explicit node_huff(std::size_t _frequency): frequency(_frequency){}
            };
            struct compareNode {
                inline bool operator()(const std::shared_ptr<node_huff> &_left,
                                        const std::shared_ptr<node_huff> &_right) const noexcept {
                                            return _left->frequency > _right->frequency;
                                        }
            };
            class branch : public node_huff {
                public:
                    const std::shared_ptr<node_huff> left;
                    const std::shared_ptr<node_huff> right;
                    const std::size_t id;
                    branch(const std::shared_ptr<node_huff> &_left,
                            const std::shared_ptr<node_huff> &_right,
                            std::size_t _id):
                            node_huff(_left->frequency + _right->frequency),
                            left(_left),right(_right),id(_id){}
            };
    };
}

#endif