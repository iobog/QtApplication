#include "validator.h"
#include <assert.h>
#include <sstream>

void ValidatorMasina::validate(const Masina& p)
{
  string msgs;
  if (p.getModel().size() == 0)msgs + "Model vid";
  if (p.getTip().size() == 0)msgs + "Tip vid";
  if (p.getProducator().size() == 0)msgs + "Producator vid";
  if (msgs.size())
  {
    throw ValidateException(msgs);
  }
}


ostream& operator<<(ostream& out, const ValidateException& ex)
{
  out << ex.msgs;
  return out;
}

void testValidator() {
  ValidatorMasina v;
  Masina p{ 1,"","","" };
  try {
    v.validate(p);
  }
  catch (const ValidateException& ex) {
    std::stringstream sout;
    sout << ex;
    const auto mesaj = sout.str();
    assert(true);
  }
}