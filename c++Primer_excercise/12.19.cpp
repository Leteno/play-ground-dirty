
#include <iostream>
#include <memory>
#include <vector>

class StrBlobPtr;

class StrBlob {
friend StrBlobPtr;
public:
    StrBlob(std::vector<int>& d) : data (std::move(d)) {}

    StrBlobPtr begin();
    StrBlobPtr end();
private:
    std::vector<int> data;
};

class StrBlobPtr {
public:
    StrBlobPtr(StrBlob& blob, int curr) :
        curr (curr), data {std::make_shared<std::vector<int>>(blob.data)} {}

    int deref() const;
    StrBlobPtr& incr();
    bool equal(StrBlobPtr&);

private:
    int curr;
    std::weak_ptr<std::vector<int>> data;
};

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this, 0);
}

StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data.size());
}

int StrBlobPtr::deref() const
{
    auto sp = data.lock();
    if (!sp) {
        throw "data is gone";
    }
    if (curr >= sp->size()) {
        throw "Out of boundary";
    }
    return (*sp)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    auto sp = data.lock();
    if (!sp) {
        throw "data is gone";
    }
    if (curr >= sp->size()) {
        throw "Out of boundary";
    }
    ++curr;
    return *this;
}

bool StrBlobPtr::equal(StrBlobPtr& ptr) {
    return /* ptr.data == data && */
            ptr.curr == curr;
}

int main()
{
    std::vector<int> data {1, 2, 3, 4, 5, 6};
    StrBlob blob(data);

    for (StrBlobPtr p = blob.begin(), end = blob.end(); !p.equal(end); p.incr()) {
        std::cout << p.deref() << std::endl;
    }

    return 0;
}