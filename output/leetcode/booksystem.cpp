// #include <iostream>
// #include <string>
// using namespace std;

// struct Book {
//     string name;
//     string author;
//     double price;
// };

// int main() {
//     const int MAX_BOOKS = 1000;  
//     Book library[MAX_BOOKS];
//     int bookCount = 0;           

//     int T;
//     cin >> T;
//     cin.ignore(); 

//     for (int t = 0; t < T; t++) {
//         string line;
//         getline(cin, line);

//         if (line.substr(0, 3) == "ADD") {
//             string name, author, price1;
//             size_t pos1 = line.find('(');
//             size_t pos2 = line.find(')', pos1);
//             name = line.substr(pos1 + 1, pos2 - pos1 - 1);

//             pos1 = line.find('(', pos2);
//             pos2 = line.find(')', pos1);
//             author = line.substr(pos1 + 1, pos2 - pos1 - 1);

//             pos1 = line.find('(', pos2);
//             pos2 = line.find(')', pos1);
//             price1 = line.substr(pos1 + 1, pos2 - pos1 - 1);
//             double price = atof(price1.c_str());

//             bool exists = false;
//             for (int i = 0; i < bookCount; i++) {
//                 if (library[i].name == name && library[i].author == author) {
//                     exists = true;
//                     break;
//                 }
//             }

//             if (exists) 
//             {
//                 cout << "FAIL"<<endl;
//             } 
//             else {
//                 library[bookCount].name = name;
//                 library[bookCount].author = author;
//                 library[bookCount].price = price;
//                 bookCount++;
//                 cout << "SUCCESS"<<endl;
//             }

//         } 
//         else if (line.substr(0, 6) == "REMOVE") {
//             string name, author;
//             size_t pos1 = line.find('(');
//             size_t pos2 = line.find(')', pos1);
//             name = line.substr(pos1 + 1, pos2 - pos1 - 1);

//             pos1 = line.find('(', pos2);
//             pos2 = line.find(')', pos1);
//             author = line.substr(pos1 + 1, pos2 - pos1 - 1);

//             bool found = false;
//           for (int i = 0; i < bookCount; i++) {
//     if (library[i].name == name && library[i].author == author) 
//     {
//         for (int j = i; j < bookCount - 1; j++) 
//         {
//             library[j] = library[j + 1];
//         }
//         bookCount--;
//         found = true;
//         break;
//     }
// }


//             if (found) 
//             {

//                 cout << "SUCCESS\n";
//             } 
//             else 
//             {
//                 cout << "FAIL\n";
//             }

//         }
//          else if (line.substr(0, 4) == "FIND") 
//          {
        
//             string name;
//             size_t pos1 = line.find('(');
//             size_t pos2 = line.find(')', pos1);
//             name = line.substr(pos1 + 1, pos2 - pos1 - 1);

//             int count = 0;
//             for (int i = 0; i < bookCount; i++) 
//             {
//                 if (library[i].name == name) 
//                 {
//                     count++;
//                 }
//             }
//             cout << count << "\n";
//         }
//     }

//     return 0;
// }
