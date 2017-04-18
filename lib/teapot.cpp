#include "../include/teapot.h"

void Teapot::draw() {
  glUseProgram(programId);

  for (UniformHandler *uh : uniformList) uh->loadElements(programId);

  glUniformMatrix4fv(rtnMtxId, 1, GL_FALSE, &rtn[0][0]);

  for (const VBO_Data & va : data.getAttribs()) {
    glEnableVertexAttribArray(va.attribNum);
    glVertexAttribPointer(va.attribNum, va.vecSize, va.dataType,
			  va.normalized, va.stride, va.address);
    glBindBuffer(GL_ARRAY_BUFFER, va.id);
  }
  glDrawArrays(data.getVertexType(), 0, data.getVertexCount());

  for (const VBO_Data & va : data.getAttribs()) {
    glDisableVertexAttribArray(va.attribNum);
  }
}
