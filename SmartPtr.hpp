// SmartPtr.hpp
#ifndef SmartPtr_hpp
#define SmartPtr_hpp

template <class T> class SmartPtr
{
private:
    class Container
    {
    public:
        T *object;
        short int count;
        
        Container(T *s)
        {
            object = s;
            count = 1;
        }
        
        ~Container()
        {
            if (object) delete object, object = 0;
        }
     };
     Container *container;
     
public:
    SmartPtr()
    {
        container = 0;
    }
    
    SmartPtr(T *obj)
    {
        if (obj)
            container = new Container(obj);
        else
            container = 0;
    }
    
    SmartPtr(SmartPtr& p)
    {
        container = 0;
        (*this) = p;
    }
    
    void dropContainer()
    {
        if (container && --container->count == 0)
                delete container;
        container = 0;
    }
    
    ~SmartPtr()
    {
        dropContainer(); 
    }
    
    T& operator * ()
    {
        return *container->object;
    }
    
    T *operator -> ()
    {
        return container ? container->object : 0;
    }
    
    SmartPtr& operator = (SmartPtr& sp)
    {
        if (container)
            dropContainer();
        container = sp.container;
        if (container) 
            container->count++; 
            
        return *this;
    }
    
    SmartPtr& operator = (T *obj)
    {
        if (container)
            dropContainer();
            
        if (obj)
            container = new Container(obj); 
            
        return *this;
    }
};

#endif

