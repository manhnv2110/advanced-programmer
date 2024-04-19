
 int* p = new int;
 int* p2 = p; // gan con tro p2 bang p, nen p va p2 cung tro vao cung 1 vung bo nho
 *p = 10; // gan gia tri 10 vao vung bo nho ma p2 va p dang tro de
 delete p;  // xoa vung bo nho p tro den
*p2 = 100;
 cout << *p2;
 delete p2; // sai o day, boi vi p2 va p cung tro den 1 vung bo nho, ma no da xoa o tren roi :)

