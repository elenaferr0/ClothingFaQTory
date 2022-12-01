#ifndef MODEL_H
#define MODEL_H

namespace Core {
  class Model
  {
    private:
      unsigned long long id;
    public:
      Model() : id(0){};
      unsigned long long getId() const;
      virtual Model* clone() const = 0;
  };
}

#endif // MODEL_H
