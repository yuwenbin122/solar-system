#pragma once

class VertexBufferLayout;//����ѭ�����ã����������ǰѺ궨��Ĳ���д�ɵ�������ͷ�ļ�������������ͷ�ļ�

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBufferLayout& layout);

	void Bind()const;
	void Unbind()const;
private:
	unsigned int m_RendererID;
};

