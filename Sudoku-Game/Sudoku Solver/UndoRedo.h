#pragma once


// UndoRedo

class UndoRedo : public CWnd
{
	DECLARE_DYNAMIC(UndoRedo)

public:
	UndoRedo();
	virtual ~UndoRedo();
	static int undo[9][9];
	static int redo[9][9];
	static bool redoable,undoable;
	static void redonow(bool aj);
	static void undonow(bool aj);
	static int ucount,rcount;
	int val;

protected:
	DECLARE_MESSAGE_MAP()
};


