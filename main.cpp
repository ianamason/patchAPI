#include <stdint.h>
#include <vector>
#include <iterator>
#include <iostream>

// symtabAPI
#include "Symtab.h"

// parseAPI
#include "CodeSource.h"
#include "CodeObject.h"
#include "CFG.h"

// patchAPI
#include "AddrSpace.h"
#include "PatchObject.h"
#include "PatchCFG.h"
#include "PatchMgr.h"


using namespace std;
using namespace Dyninst;
using namespace PatchAPI;


class NoopSnippet : public Snippet {

public:
  bool generate(Point *pt, Buffer &buffer){
    uint8_t byte = 0x90;
    cerr << "NoopSnippet.generate: inserting a no op\n" << endl;
    buffer.push_back(byte);
    return true;
  }

};


int main(int argc, const char *argv[]) {

  if(argc != 3){
    cerr << "Usage:\n\t" << argv[0] << " <input binary> <output binary path>" << endl;

  }
  const char* input_binary = argv[1];
  const char* output_binary = argv[2];

  /* Open the specified binary */
  SymtabAPI::Symtab *symtab = NULL;
  if(!SymtabAPI::Symtab::openFile(symtab, input_binary)) {
    cerr <<  "SymtabAPI::Symtab couldn't open: " << input_binary << endl;
    return 1;
  }

  ParseAPI::SymtabCodeSource *sts = new ParseAPI::SymtabCodeSource(symtab);

  ParseAPI::CodeObject *co = new ParseAPI::CodeObject(sts, NULL, NULL);

  PatchObject* binobj =  PatchObject::create(co, 0);

  AddrSpace* as = AddrSpace::create(binobj);

  PatchMgrPtr patchMgr = PatchMgr::create(as);

  Patcher patcher(patchMgr);

  NoopSnippet::Ptr snippet = NoopSnippet::create(new NoopSnippet);

  vector<PatchFunction*> functions;

  binobj->funcs(back_inserter(functions));

  for(vector<PatchFunction*>::iterator funIter = functions.begin(); funIter != functions.end(); funIter++){
    PatchFunction *fun = *funIter;

    vector<Point*> f_entryPoints;
    patchMgr->findPoints(PatchAPI::Scope(fun), PatchAPI::Point::FuncEntry, back_inserter(f_entryPoints));


    cout << fun->name() << " has:\n\t" << f_entryPoints.size() << " entry points" << endl;

    for(vector<Point*>::iterator pointIter = f_entryPoints.begin(); pointIter!= f_entryPoints.end(); pointIter++){
      Point* point = *pointIter;
      cerr << "PATCHING" << endl;
      patcher.add(PushBackCommand::create(point, snippet));
    }

  }

  patcher.commit();

  // maybe we need to write something else out?
  symtab->emit(output_binary);


  cout << "OK" << endl;

}
