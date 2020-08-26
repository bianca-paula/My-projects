#pragma once
#include "Service.h"
#include "Domain.h"
#include "Repository.h"

class ActionUndoRedo {
public:
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	ActionUndoRedo()  {}
	virtual ~ActionUndoRedo() = default;
};

class UndoRedo_Add : public ActionUndoRedo {
	Evidence evidence;
	Repository& repository;
public:
	UndoRedo_Add(Repository& repository, const Evidence& evidence) : repository{ repository }, evidence{ evidence }{}
	void Undo() override {
		repository.delete_evidence(evidence);
	}
	void Redo() override {
		repository.add_evidence(evidence);
	}
};

class UndoRedo_Delete : public ActionUndoRedo {
	Evidence evidence;
	Repository& repository;
public:
	UndoRedo_Delete(Repository& repository, const Evidence& evidence) : repository{ repository }, evidence{ evidence }{}
	void Undo() override {
		repository.add_evidence(evidence);
	}
	void Redo() override {
		repository.delete_evidence(evidence);
	}
};

class UndoRedo_Update : public ActionUndoRedo
{
	Evidence evidence;
	Evidence evidence_after_update;
	Repository& repository;
public:
	UndoRedo_Update(Repository& repository, const Evidence& evidence, const Evidence& evidence_after_update) : repository{ repository }, evidence{ evidence }, evidence_after_update{ evidence_after_update } {}
	void Undo() override {
		repository.update_evidence(evidence);
	}
	void Redo() override {
		repository.update_evidence(evidence_after_update);
	}
};


