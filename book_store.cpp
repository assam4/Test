#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
const int Empty = 0 ;
const int Step = 100 ;
const string Book_t = "Book" ;
const string Magazine_t = "Magazine" ;

class Resource
{
    public:
            Resource():m_index(Empty) {}
            Resource(const string& ,const string& ,int);
            virtual ~Resource() {}
            virtual void displayDetails(ostream& os) const = 0;
            virtual bool read(istream& is) = 0;


    protected:
            int m_index;
            string m_title;
            string m_author;
};

Resource::Resource(const string& t ,const string& a ,int i)
            :m_index(i) ,m_title(t) , m_author(a)
{ }

class Book : public Resource
{
    public:
    Book():m_numpages(Empty){}
    Book(const string& ,const string& ,int ,int) ;
    void displayDetails(ostream& ) const override ;
    bool read(istream& ) override;

    private:
    int m_numpages;
};

Book::Book(const string& t,const string& a,int i,int np)
        :Resource(t,a,i) , m_numpages(np)
{ }

void Book::displayDetails(ostream& os) const
{
   os << "Type: "   << Book_t << " , "
      << "Title: "  << m_title << " , " 
      << "Author: " << m_author << " , "
      << "Index: "  << m_index << " , "
      << "Pages: "  << m_numpages << endl ;
}

bool Book::read(istream& is)
{
    
        is.ignore(Step,':');
        is >> m_title;
        is.ignore(Step,':');
        is >> m_author;
        is.ignore(Step,':');
        is >> m_index;
        is.ignore(Step,':');
        is >> m_numpages;
        
    if(m_title.empty() || m_author.empty() 
       || m_index==Empty || m_numpages == Empty)
    return false;
    return true;
}

class Magazine:public Resource
{
    public:
            Magazine():m_issuenumber(Empty){}
            Magazine(const string& ,const string& ,int ,int) ;
            void displayDetails(ostream& os) const override ;
            bool read(istream& is) override ;
    private:
            int m_issuenumber;
};

Magazine::Magazine(const string& t,const string& a,int i,int is)
        :Resource(t,a,i) , m_issuenumber(is)
{ }

void Magazine::displayDetails(ostream& os) const
{
   os << "Type: " << Magazine_t << " , "
      << "Title: " << m_title << " , " 
      << "Author: " << m_author << " , "
      << "Index: "  << m_index << " , "
      << "Issuenumber: "  << m_issuenumber << endl ;
}

bool Magazine::read(istream& is)
{
        is.ignore(Step,':');
        is >> m_title;
        is.ignore(Step,':');
        is >> m_author;
        is.ignore(Step,':');
        is >> m_index;
        is.ignore(Step,':');
        is >> m_issuenumber;
    if(m_title.empty() || m_author.empty() 
       || m_index==Empty || m_issuenumber == Empty)
    return false;
    return true;
}

class I_O
{
  public:
   I_O(istream& ,ostream& );
   bool read();
   bool write();

   private:
   istream& m_is;
   ostream& m_os;
   vector<Resource*> m_store;

};

I_O::I_O(istream& i , ostream& o):m_is(i) ,m_os(o)
{ }

bool I_O::read()
{
    while(!m_is.eof())
    {
      m_is.ignore(Step,':') ;
      string type;
      m_is >> type ;
      if(type == Book_t)
      {
        Book object;
        if(object.read(m_is))
        m_store.push_back(&object);
        else return false;
      }
      else if(type == Magazine_t)
      {
        Magazine object;
        if(object.read(m_is))
        m_store.push_back(&object);
        else return false;
      }
    
    }
    return true;
}

bool I_O::write()
{
    if(m_store.empty()) return false;
    for(auto var : m_store)
    { m_os << "{" ;
    var->displayDetails(m_os);
      m_os << "}" ;
    }
    return true ;
}


void Interface()
{
  cout << "Hello,lets check what you want :) add or see" << endl ;
  string choice ;
  cin >> choice ;
  if(choice == "add")
  {
    ofstream os("Ourlist.txt");
    if(os.is_open())
    I_O for_salers(cin,os);

  }

  else if(choice == "see")
  {
    ifstream is("Ourlist.txt");
    if(is.is_open())
    I_O for_readers(is,cout);
  }
  
}
int main()
{
    Interface();
    return 0 ;
}

