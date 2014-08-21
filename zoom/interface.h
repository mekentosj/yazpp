// ZOOM C++ Binding.
// The ZOOM homepage is at http://zoom.z3950.org/
//
// Derived from version 1.3a at
//	http://zoom.z3950.org/bind/cplusplus/zoom-1.3a.hh

#include <stddef.h>		// for size_t
#include <string>


namespace ZOOM {
  // Forward declarations for type names.
  class query;
  class resultSet;
  class record;

  class connection {
    // connections are non-copyable.
    connection (const connection &);
    connection &operator= (const connection &);
  public:
    connection ();
    connection (const std::string &hostname, int portnum);
    ~connection ();
    void connect (const std::string &hostname, int portnum);
    std::string option (const std::string &key) const;
    bool option (const std::string &key, const std::string &val);
  };

  class query {
      // base class for all query types
  public:
    query ();
    virtual ~query ();
  };

  class prefixQuery : public query {
  public:
    prefixQuery (const std::string &pqn);
    ~prefixQuery ();
  };

  class CCLQuery : public query {
  public:
    CCLQuery (const std::string &ccl, void *qualset);
    ~CCLQuery ();
  };

  class resultSet {
    // resultSets are non-copyable.
    resultSet (const resultSet &);
    resultSet &operator= (const resultSet &);
  public:
    resultSet (connection &c, const query &q);
    ~resultSet ();
    std::string option (const std::string &key) const;
    bool option (const std::string &key, const std::string &val);
    size_t size () const;
  };

  class record {
  public:
    class syntax {
    public:
      enum value {
	UNKNOWN, GRS1, SUTRS, USMARC, UKMARC, XML
      };
      syntax (value rs);
      operator std::string () const;
      bool operator== (const syntax &s) const;
      bool operator== (value rs) const;
      operator value () const;
    };

    record (resultSet &rs, size_t num);
    ~record ();
    syntax recsyn () const;
    std::string render () const;
    std::string rawdata () const;
  };

  // Base exception class; from which all other ZOOM exceptions
  // are derived. Other classes that use this as their base
  // class may want to provide their own errcode() and errmsg()
  // functions -- hence they are made virtual.
  class exception {
  public:
    exception (int code);
    virtual ~exception ();
    virtual int errcode () const;
    virtual std::string errmsg () const;
  };

  // systemException could be thrown for timeouts, protocol errors,
  // network outages.
  class systemException : public exception {
  public:
    systemException ();		// Uses value of system `errno'
    systemException (int code);
  };

  // bib1Exception::errcode() returns a code from the
  // Bib-1 Diagnostic Set.
  class bib1Exception: public exception {
  public:
    bib1Exception (int code, const std::string &addinfo);
    std::string addinfo () const;
  };

  class queryException : public exception {
  public:
    enum { PREFIX, CCL };
    queryException (int qtype, const std::string &source);
    std::string addinfo () const;
  };
}
