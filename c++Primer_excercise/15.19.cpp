
class Base {
};
class DerivePublic : public Base {
public:
    void memfcn(Base &b) { b = *this; }
};
class DeriveProtect : protected Base {
public:
    void memfcn(Base &b) { b = *this; }
};
class DerivePrivate : private Base {
public:
    void memfcn(Base &b) { b = *this; }
};

int main()
{
    DerivePrivate priv;
    DeriveProtect protect;
    DerivePublic pub;

    Base b;
    priv.memfcn(b);
    protect.memfcn(b);
    pub.memfcn(b);

    return 0;
}