// Registro auxiliar para guardar una referencia a un objeto y que solo la clase
// de dicho objeto pueda registrar en dicho registro
template <typename T> 
class SelfRegisteredRegistry{
public:
    inline SelfRegisteredRegistry(): value(nullptr) {};
    inline T& getValue() { return *value; }

private:
    T* value;
    
    friend T;
};