#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T* getInstance() {
        if (instance == nullptr) {
            instance = new T();
        }
        return instance;
    }

    virtual ~Singleton() {
        delete instance;
    }

protected:
    Singleton() = default;

private:
    static T* instance;
};

template <typename T>
T* Singleton<T>::instance = nullptr;

#endif //SINGLETON_H
