/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2022 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "macroInt.h"
#include "instrument.h"

void DivMacroStruct::doMacro(DivInstrumentMacro& source, bool released) {
  if (finished) finished=false;
  if (had!=has) {
    finished=true;
  }
  had=has;
  if (has) {
    val=source.val[pos++];
    if (source.rel>=0 && pos>source.rel && !released) {
      if (source.loop<source.len && source.loop>=0 && source.loop<source.rel) {
        pos=source.loop;
      } else {
        pos--;
      }
    }
    if (pos>=source.len) {
      if (source.loop<source.len && source.loop>=0 && (source.loop>=source.rel || source.rel>=source.len)) {
        pos=source.loop;
      } else {
        has=false;
      }
    }
  }
}

void DivMacroInt::next() {
  if (ins==NULL) return;
  // run macros
  // TODO: potentially get rid of list to avoid allocations
  if (!macroList.empty()) {
      for (std::list<DivMacroExecList>::iterator iter = macroList.begin(); iter!= macroList.end(); iter++) {
        iter->doMacro(released);
    }
  }
}

void DivMacroInt::release() {
  released=true;
}

void DivMacroInt::init(DivInstrument* which) {
  ins=which;
  // initialize
  // TODO: potentially get rid of list to avoid allocations
  while (!macroList.empty()) {
    macroList.front().init();
    macroList.pop_front();
  }

  released=false;

  if (ins==NULL) return;

  // prepare common macro
  if (ins->std.volMacro.len>0) {
    macroList.push_back(DivMacroExecList(vol,ins->std.volMacro));
  }
  if (ins->std.arpMacro.len>0) {
    macroList.push_back(DivMacroExecList(arp,ins->std.arpMacro));
  }
  if (ins->std.dutyMacro.len>0) {
    macroList.push_back(DivMacroExecList(duty,ins->std.dutyMacro));
  }
  if (ins->std.waveMacro.len>0) {
    macroList.push_back(DivMacroExecList(wave,ins->std.waveMacro));
  }
  if (ins->std.pitchMacro.len>0) {
    macroList.push_back(DivMacroExecList(pitch,ins->std.pitchMacro));
  }
  if (ins->std.ex1Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex1,ins->std.ex1Macro));
  }
  if (ins->std.ex2Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex2,ins->std.ex2Macro));
  }
  if (ins->std.ex3Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex3,ins->std.ex3Macro));
  }
  if (ins->std.algMacro.len>0) {
    macroList.push_back(DivMacroExecList(alg,ins->std.algMacro));
  }
  if (ins->std.fbMacro.len>0) {
    macroList.push_back(DivMacroExecList(fb,ins->std.fbMacro));
  }
  if (ins->std.fmsMacro.len>0) {
    macroList.push_back(DivMacroExecList(fms,ins->std.fmsMacro));
  }
  if (ins->std.amsMacro.len>0) {
    macroList.push_back(DivMacroExecList(ams,ins->std.amsMacro));
  }

  if (ins->std.panLMacro.len>0) {
    macroList.push_back(DivMacroExecList(panL,ins->std.panLMacro));
  }
  if (ins->std.panRMacro.len>0) {
    macroList.push_back(DivMacroExecList(panR,ins->std.panRMacro));
  }
  if (ins->std.phaseResetMacro.len>0) {
    macroList.push_back(DivMacroExecList(phaseReset,ins->std.phaseResetMacro));
  }
  if (ins->std.ex4Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex4,ins->std.ex4Macro));
  }
  if (ins->std.ex5Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex5,ins->std.ex5Macro));
  }
  if (ins->std.ex6Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex6,ins->std.ex6Macro));
  }
  if (ins->std.ex7Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex7,ins->std.ex7Macro));
  }
  if (ins->std.ex8Macro.len>0) {
    macroList.push_back(DivMacroExecList(ex8,ins->std.ex8Macro));
  }

  // prepare FM operator macros
  for (int i=0; i<4; i++) {
    DivInstrumentSTD::OpMacro& m=ins->std.opMacros[i];
    IntOp& o=op[i];
    if (m.amMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.am,m.amMacro));
    }
    if (m.arMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.ar,m.arMacro));
    }
    if (m.drMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.dr,m.drMacro));
    }
    if (m.multMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.mult,m.multMacro));
    }
    if (m.rrMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.rr,m.rrMacro));
    }
    if (m.slMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.sl,m.slMacro));
    }
    if (m.tlMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.tl,m.tlMacro));
    }
    if (m.dt2Macro.len>0) {
      macroList.push_back(DivMacroExecList(o.dt2,m.dt2Macro));
    }
    if (m.rsMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.rs,m.rsMacro));
    }
    if (m.dtMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.dt,m.dtMacro));
    }
    if (m.d2rMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.d2r,m.d2rMacro));
    }
    if (m.ssgMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.ssg,m.ssgMacro));
    }

    if (m.damMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.dam,m.damMacro));
    }
    if (m.dvbMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.dvb,m.dvbMacro));
    }
    if (m.egtMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.egt,m.egtMacro));
    }
    if (m.kslMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.ksl,m.kslMacro));
    }
    if (m.susMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.sus,m.susMacro));
    }
    if (m.vibMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.vib,m.vibMacro));
    }
    if (m.wsMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.ws,m.wsMacro));
    }
    if (m.ksrMacro.len>0) {
      macroList.push_back(DivMacroExecList(o.ksr,m.ksrMacro));
    }
  }

  if (!macroList.empty()) {
    for (std::list<DivMacroExecList>::iterator iter = macroList.begin(); iter!= macroList.end(); iter++) {
      iter->prepare();
    }
  }
}

void DivMacroInt::notifyInsDeletion(DivInstrument* which) {
  if (ins==which) {
    init(NULL);
  }
}
