#version 330 core
//--- out_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- FragColor: ����� ������ ������ ������ ���۷� ���� ��.

in vec3 out_Color; //--- ���ؽ� ���̴����Լ� ���� ����

out vec4 FragColor; //--- ���� ���

void main(void)
{
	FragColor = vec4 (out_Color, 1.0);
}