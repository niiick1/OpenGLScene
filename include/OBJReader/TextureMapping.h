#ifndef TEXTUREMAPPING_H
#define TEXTUREMAPPING_H


class TextureMapping
{
    public:
        TextureMapping(float u, float v);
        virtual ~TextureMapping();

        float u() const { return _u; }
        float v() const { return _v; }
    protected:
    private:
        float _u, _v;
};

#endif // TEXTUREMAPPING_H
