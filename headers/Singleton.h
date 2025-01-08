#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * @brief Template class implementing the Singleton design pattern.
 */
template <typename T>
class Singleton {
public:
    /**
     * @brief Deleted copy constructor.
     */
    Singleton(const Singleton&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     *
     * @return A reference to the current Singleton object.
     */
    Singleton& operator=(const Singleton&) = delete;

    /**
     * @brief Returns the unique instance of the Singleton class.
     *
     * @return A pointer to the unique instance of the class.
     */
    static T* getInstance() {
        if (instance == nullptr) {
            instance = new T();  ///< Create a new instance if it doesn't exist.
        }
        return instance;
    }

    /**
     * @brief Destructor for the Singleton class.
     */
    virtual ~Singleton() {
        delete instance;  ///< Free the allocated memory for the singleton instance.
    }

protected:
    /**
     * @brief Protected constructor to prevent instantiation.
     */
    Singleton() = default;

private:
    static T* instance;  ///< Static pointer to hold the unique instance of the class.
};

/**
 * @brief Initializes the static instance pointer to nullptr.
 */
template <typename T>
T* Singleton<T>::instance = nullptr;


#endif //SINGLETON_H
