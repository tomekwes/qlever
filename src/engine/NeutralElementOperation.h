// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Johannes Kalmbach (kalmbach@cs.uni-freiburg.de)

#ifndef QLEVER_SRC_ENGINE_NEUTRALELEMENTOPERATION_H
#define QLEVER_SRC_ENGINE_NEUTRALELEMENTOPERATION_H

#include "engine/Operation.h"

/// The neutral element wrt `JOIN`. It contains one element, but binds no
/// variables (which means it has 0 columns).
class NeutralElementOperation : public Operation {
 public:
  explicit NeutralElementOperation(QueryExecutionContext* qec)
      : Operation{qec} {}
  std::vector<QueryExecutionTree*> getChildren() override { return {}; }

 private:
  // The individual implementation of `getCacheKey` (see above) that has to be
  // customized by every child class.
  [[nodiscard]] std::string getCacheKeyImpl() const override {
    return "Neutral Element";
  };

 public:
  [[nodiscard]] std::string getDescriptor() const override {
    return "NeutralElement";
  };
  [[nodiscard]] size_t getResultWidth() const override { return 0; };
  size_t getCostEstimate() override { return 0; }

 private:
  uint64_t getSizeEstimateBeforeLimit() override { return 1; }

 public:
  float getMultiplicity(size_t) override { return 0; };
  bool knownEmptyResult() override { return false; };

  std::unique_ptr<Operation> cloneImpl() const override {
    return std::make_unique<NeutralElementOperation>(_executionContext);
  }

 protected:
  [[nodiscard]] std::vector<ColumnIndex> resultSortedOn() const override {
    return {};
  };

 private:
  Result computeResult([[maybe_unused]] bool requestLaziness) override {
    IdTable idTable{getExecutionContext()->getAllocator()};
    idTable.setNumColumns(0);
    idTable.resize(1);
    return {std::move(idTable), resultSortedOn(), LocalVocab{}};
  }

  [[nodiscard]] VariableToColumnMap computeVariableToColumnMap()
      const override {
    return {};
  };
};

#endif  // QLEVER_SRC_ENGINE_NEUTRALELEMENTOPERATION_H
