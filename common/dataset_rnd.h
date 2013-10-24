// -*- mode: c++; coding: utf-8 -*-

#ifndef JUBATUS_X_BENCH_DATASET_SVM_
#define JUBATUS_X_BENCH_DATASET_SVM_

#include <fstream>
#include <tr1/memory>
#include <pficommon/lang/cast.h>
#include <pficommon/math/random.h>

#include "dataset.h"
#include "exception.h"

namespace jubatus {
namespace bench {

template<typename DATUM>
class DatasetRND : public Dataset {
public:
  typedef DATUM datum_type;
  typedef std::pair<std::string, datum_type> label_datum_type;
  typedef std::tr1::shared_ptr<label_datum_type> label_datum_ptr;

public:
  virtual ~DatasetRND() {}

public:
  const label_datum_type &get(size_t i) {
    return *(data_[i%data_.size()]);
  }
  virtual size_t size() const {
    return data_.size();
  }
  virtual std::string description() const {
    return "Random dataset";
  }

  virtual void load(const size_t count) {
    pfi::math::random::mtrand rnd;
    for (size_t dat_no = 0; dat_no < count; dat_no++ ) {
      label_datum_ptr d = generate_random_label_datum(rnd);
      if ( d ) data_.push_back(d);
    }
  }

private:
  label_datum_ptr generate_random_label_datum(pfi::math::random::mtrand rnd) {

    std::string label;
    if (rnd.next_int() % 2 == 0)
      label = "positive";
    else
      label = "negative";

    std::vector<std::pair<std::string, double> > num_values;

    for (size_t idc = 0; idc < 5; idc++ ) {
      std::string id = pfi::lang::lexical_cast<std::string>(idc);
      double val = rnd.next_double();
      num_values.push_back(make_pair(id, val));
    }

    label_datum_ptr result( new label_datum_type() );
    result->first.swap(label);
    result->second.string_values.clear();
    result->second.num_values.swap(num_values);

    return result;
  }

  std::vector<label_datum_ptr> data_;
};

} // namespace bench
} // namespace jubatus

#endif // JUBATUS_X_BENCH_DATASET_SVM_
