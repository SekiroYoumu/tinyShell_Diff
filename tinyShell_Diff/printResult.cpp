#pragma once
#include "header.h"
void printResult(stack<LineRelation> line, char** a, char** b, int n, int m,bool ignoreBl)
{
	string output_buffer; //��stringģ��strout�Ļ�����
	LineRelation now;
	while (line.size() > 0)
	{
		now = line.top();
		/*���㷨�����֪��һ����ɾ�����������ʡ����ġ���������λΪdʱ����*/
		if (now.op == 'd') //���ȳ��ֵ�Ϊd
		{
			char op = 'd';
			bool dflag = 0, aflag = 0;
			LineRelation start, add_start, end, tmp;
			start = now;
			while (line.size() > 0)
			{
				tmp = now;
				now = line.top();
				if (now.op == 'd')
				{
					if (now.x != start.x)
						dflag = 1;
				}
				else if (now.op == 'a')
				{
					if (aflag == 0)
					{
						op = 'c';
						add_start = now;
						aflag = 1;
					}
				}
				if (now.op == '=')
				{
					end = tmp;
					break;
				}
				line.pop();
				if (line.size() == 0)
				{
					end = now;
					break;
				}
			}
			int end_x = start.x;
			int start_y = end.y;
			output_buffer.append(to_string(start.x));
			if (dflag == 1)
			{
				if (aflag == 1)  end_x = add_start.x;
				else end_x = end.x;
				output_buffer.append(1, ',');
				output_buffer.append(to_string(end_x));
			}
			output_buffer.append(1, op);
			if (aflag == 1 && add_start.y != end.y)
			{
				start_y = add_start.y;
				output_buffer.append(to_string(start_y));
				output_buffer.append(1, ',');
			}
			output_buffer.append(to_string(end.y));
			output_buffer.append(1, '\n');
			for (int i = start.x; i <= end_x; i++)
			{
				output_buffer.append(1, '<');
				output_buffer.append(a[i - 1]);
				output_buffer.append(1, '\n');
			}
			if (end_x == n)
				output_buffer.append("\\ No newline at end of file\n");
			if (op == 'c')
			{
				output_buffer.append("---\n");
				for (int j = start_y; j <= end.y; j++)
				{
					output_buffer.append(1, '>');
					output_buffer.append(b[j - 1]);
					output_buffer.append(1, '\n');
				}
				if (end.y == m)
					output_buffer.append("\\ No newline at end of file\n");
			}
			strcat_s(gTerm.strout, output_buffer.c_str());//�������Ƴ�
			output_buffer = "";//���������
		}
		else if (now.op == 'a')//���ȳ��ֵ�Ϊa�����㷨�����֪�������ڵ�һ��ȫ��a
		{
			LineRelation start, tmp;
			start = now;
			tmp = now;
			while (line.size() > 0)
			{
				now = line.top();
				if (now.op != 'a') break;
				tmp = now;
				line.pop();
				if (line.size() == 0) break;
			}
			int end_y = start.y;
			output_buffer.append(to_string(start.x));
			output_buffer.append(1, 'a');
			output_buffer.append(to_string(start.y));
			if (tmp.y != start.y)
			{
				if (now.op == 'a') end_y = now.y;
				else end_y = tmp.y;
				output_buffer.append(1, ',');
				output_buffer.append(to_string(end_y));
				output_buffer.append(1, '\n');
			}
			else output_buffer.append(1, '\n');
			for (int i = start.y; i <= end_y; i++)
			{
				output_buffer.append(1, '>');
				output_buffer.append(b[i - 1]);
				output_buffer.append(1, '\n');
			}
			if (end_y == m)
				output_buffer.append("\\ No newline at end of file\n");
		}
		strcat_s(gTerm.strout, output_buffer.c_str());//�������Ƴ�
		output_buffer = "";//���������
		if (now.op == '=');
		if (line.size() <= 1) break;
		line.pop();
	}
	return;
}//ͨ������ջ��ý�����