#include <iostream>
#include <string>
#include <cstddef>   

class VeryHeavyDatabase {
public:
    virtual ~VeryHeavyDatabase() {}

    virtual std::string GetData(const std::string& key) {
        return "value";   
    }
};

class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* real_object_;
    size_t shots_;

public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_object_(real_object), shots_(shots) {}

    std::string GetData(const std::string& key) override {
        if (shots_ > 0) {
            --shots_;                               
            return real_object_->GetData(key);        
        }
        return "error";                                
    }
};

int main() {
    VeryHeavyDatabase real_db;

    OneShotDB limit_db(&real_db, 2);

    std::cout << limit_db.GetData("key") << std::endl;  
    std::cout << limit_db.GetData("key") << std::endl;  
    std::cout << limit_db.GetData("key") << std::endl;  

    return 0;
}