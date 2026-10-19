#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>

enum class Gender{
    man,
    woman,
    unkown
};

// 重载输出运算符
std::ostream& operator<<(std::ostream& os, Gender g) {
    switch(g) {
        case Gender::man:   os << "man"; break;
        case Gender::woman: os << "woman"; break;
        case Gender::unkown:os << "unkown"; break;
        default: break;
    }
    return os;
}

class Person
{
public:
    Person()
    :m_name(), m_gender(Gender::unkown), m_phone("Unkown"){}

    Person(const std::string name, const Gender gender, const std::string phone) 
    :m_name(name), m_gender(gender), m_phone(phone){
    }

    void PrintInfo(){
        std::cout << "the name is   : " << m_name << std::endl;
        std::cout << "the gender is : " << genderToString(m_gender) << std::endl;
        std::cout << "the gender is : " << m_gender << std::endl;
        std::cout << "the phone number is: " << m_phone << std::endl;
    }
private:
    std::string m_name;
    Gender m_gender;
    std::string m_phone;
        // 辅助函数：将 Gender 转换为字符串
    std::string genderToString(Gender g) const {
        switch(g) {
            case Gender::man:   return "man";
            case Gender::woman: return "woman";
            default:            return "unknown";
        }
    }
};

int main()
{
    std::vector<Person> p_vector;
    Person p1("Alice", Gender::woman, "2321343248");
    Person p2;
    Person p3;
    p1.PrintInfo();

    p_vector.push_back(p1);
    p_vector.push_back(p2);
    p_vector.push_back(p3);
    for (auto i  : p_vector) {
        i.PrintInfo();
    }
    return 0;
}










