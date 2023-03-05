#include "Frame.h"


void blitFrame(Frame frame, int u, int v, std::vector<glm::vec4> pixels){
	glBindTexture(GL_TEXTURE_2D, frame.texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, u, v, 0, GL_RGBA, GL_FLOAT, pixels.data());
	glBindFramebuffer(GL_READ_FRAMEBUFFER, frame.framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, u, v, 0, 0, u, v,GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
