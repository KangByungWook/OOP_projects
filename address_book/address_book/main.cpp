// 포인트: stl 사용하지 않고 퀵소트를 클래스인스턴스 sorting에 적용



#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Person{
public:
    string name, phone_number, email_address;
    Person(){};
    Person(string name, string phone_number, string email_address)
    :name(name),phone_number(phone_number),email_address(email_address){}
    
};

Person* get_in_memory(string path, int person_num);
void quickSort(Person names[], int array_size);
void q_sort(Person persons[], int left, int right);
//sorting되면서 리스트 업데이트
void update_list(string path, Person persons[], int array_num);
Person insert_entry();

int main(int argc, const char * argv[]) {
    Person* persons = get_in_memory("address_book.txt",200);
    quickSort(persons, 13);
    for(int i = 0 ; i < 13 ; i++){
        cout << persons[i].name << ends << persons[i].phone_number << ends << persons[i].email_address << endl;
    }
    update_list("address_book.txt", persons, 13);
    persons[13] = insert_entry();
    update_list("address_book.txt", persons, 14);
    return 0;
}

Person insert_entry(){
    string name, phone_number, email_address;
    cout << "이름: ";
    cin >> name;
    cout << "전화번호: ";
    cin >> phone_number;
    cout << "이메일 주소: ";
    cin >> email_address;
    return Person(name, phone_number, email_address);
}

Person* get_in_memory(string path, int person_num){
    fstream ifile;
    
    char line[200]; // 한 줄씩 읽어서 임시로 저장할 공간
    int i = 0, j, index = 0;
    size_t space_index;
    Person* persons = new Person[200];
    ifile.open(path);  // 파일 열기
    
    if (ifile.is_open())
    {
        while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
        {
            if(i++ == 0)continue;
            Person* person_p = new Person;
            string tmp_str = string(line);
            //j : 0(하나도 추가 안함), 1(이름 추가된 상태), 2(전화번호 추가된 상태), 3(모든항목 추가완료)
            for(j = 0 ; j < 3 ; j++){
                space_index = tmp_str.find(" ");
                switch (j) {
                    case 0:
                        person_p->name = tmp_str.substr(0,space_index);
                        break;
                    case 1:
                        person_p->phone_number = tmp_str.substr(0,space_index);
                        break;
                    case 2:
                        person_p->email_address = tmp_str.substr(0,space_index);
                        break;
                        
                    default:
                        break;
                }
                tmp_str.erase(0,space_index+1);
            }
            persons[index] = *person_p;
            delete person_p;
            index++;
        }
    }
    ifile.close(); // 파일 닫기
    return persons;
}

void update_list(string path, Person persons[], int array_num){
    ofstream ofile;
    ofile.open(path);
    
    // 파일 쓰기
    ofile << "이름      전화번호            이메일" << endl;
    for (int i = 0; i < array_num; i++)
    {
        ofile << persons[i].name << ' ' << persons[i].phone_number << ' ' << persons[i].email_address << endl;
    }
    
    ofile.close(); // 파일닫기
}

void quickSort(Person names[], int array_size)
{
    q_sort(names, 0, array_size -1);
}

void q_sort(Person persons[], int left, int right)
{
    int pivot, l_hold, r_hold;
    string pivot_value;
    l_hold  = left;
    r_hold  = right;
    pivot_value = persons[left].name;  // 0번째 원소를 피봇으로 선택
    Person person_inst = persons[left];
    while (left < right)
    {
        // 값이 선택한 피봇과 같거나 크다면, 이동할 필요가 없다
        while ((persons[right].name.compare(pivot_value) > 0) && (left < right))
            right --;
        
        // 그렇지 않고 값이 피봇보다 작다면,
        // 피봇의 위치에 현재 값을 넣는다.
        if (left != right)
        {
            persons[left] = persons[right];
        }
        // 왼쪽부터 현재 위치까지 값을 읽어들이면서
        // 피봇보다 큰 값이 있다면, 값을 이동한다.
        while ((persons[left].name.compare(pivot_value) < 0) && (left < right))
            left ++;
        
        if (left != right)
        {
            persons[right] = persons[left];
            right --;
        }
    }
    
    // 모든 스캔이 끝났다면, 피봇값을 현재 위치에 입력한다.
    // 이제 피봇을 기준으로 왼쪽에는 피봇보다 작거나 같은 값만 남았다.
    persons[left] = person_inst;
    pivot         = left;
    left          = l_hold;
    right         = r_hold;
    
    // 재귀호출을 수행한다.
    if (left < pivot)
        q_sort(persons, left, pivot - 1);
    if (right > pivot)
        q_sort(persons, pivot+1, right);
}


