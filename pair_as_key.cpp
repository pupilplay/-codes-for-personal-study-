//������Visual studio 2022
#include<iostream>
#include<unordered_map>
#include<functional>
#include<map>
#include<unordered_set>
using namespace std;
//1.�ɵ��ö��������α����(����operator()����)������ָ�����(����operator ����ָ��() )��lambda���ʽ�����Ա����ָ���
/*2.����map��unordered_map��������key��const���Σ����ܵ���û��const���εĺ�����������Ҫ��const���κ�����
lambda���ʽ�õ��ĺ���Ĭ�ϱ�const���Σ���mutableʱ��ȡ��const����*/
class pair_hash_xor//ʹ�����ʵ��hash���򵥵���ϣ��ͻ���أ���{a,b}��{b,a}��ͻ
{
public:
	template<typename T1, typename T2>
	int operator()(const pair<T1, T2>& p) const
	{
		return hash<T1>()(p.first) ^ hash<T2>()(p.second);
	}
};

class pair_hash//ժ����https://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html
{
public:
	template<typename T1, typename T2>
	int operator()(const pair<T1, T2>& p) const
	{
		//����seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		//hash_valueΪ��ϣ������0x9e3779b9Ϊħ�����֣������������ڴ������֣����������
		int seed = 0;
		seed ^= hash<T1>()(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= hash<T2>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};
class pair_eq
{
public:
	template<typename T1,typename T2>
	bool operator()(const pair<T1, T2>& p1, const pair<T1, T2>& p2) const
	{
		return p1.first == p2.first && p1.second == p2.second;
	}
};

class pair_less//�����У����ȱȽ�pair��firstֵ���ٱȽ�secondֵ
{
public:
	template<typename T1, typename T2>
	bool operator()(const pair<T1, T2>& p1, const pair<T1, T2>& p2) const
	{
		if (p1.first < p2.first)
		{
			return true;
		}
		else if (p1.first == p2.first)
		{
			return p1.second < p2.second ? true : false;
		}
		else
		{
			return false;
		}
	}
};

void pair_as_map_key()
{
	map < pair<int, int>, int, pair_less>m;
	m[{1, 2}] = 10;
	m[{3, 4}] = 20;
	m[{1, 1}] = 10;
	m[{3, 3}] = 20;
	m[{1, 2}] = 10;
	m[{5, 1}] = 20;
	for (auto& x : m)
	{
		cout << "{" << x.first.first << "," << x.first.second << "}" << "->" << x.second << endl;
	}
	return;
}

void pair_as_map_key_lambda()
{
	auto pair_less_lambda = [](const auto& p1, const auto& p2) ->bool
		{
			if (p1.first < p2.first)
			{
				return true;
			}
			else if (p1.first == p2.first)
			{
				return p1.second < p2.second ? true : false;
			}
			else
			{
				return false;
			}
		};
	map < pair<int, int>, int, decltype(pair_less_lambda)>m;
	m[{1, 2}] = 10;
	m[{3, 4}] = 20;
	m[{1, 1}] = 10;
	m[{3, 3}] = 20;
	m[{1, 2}] = 10;
	m[{5, 1}] = 20;
	for (auto& x : m)
	{
		cout << "{" << x.first.first << "," << x.first.second << "}" << "->" << x.second << endl;
	}
	return;
}
void pair_as_hashmap()
{
	unordered_map <pair<int, int>, int, pair_hash, pair_eq>hash_map;
	hash_map[{1, 3}] = 1;
	hash_map[{3, 5}] = 2;
	hash_map[{4, 2}] = 3;
	hash_map[{3, 1}] = 5;
	hash_map[{1, 3}] = 4;
	hash_map[{2, 6}] = 6;
	for (auto& x : hash_map)
	{
		cout << "{" << x.first.first << "," << x.first.second << "}" << "->" << x.second << endl;
	}
	return;
}
void pair_as_hashmap_lambda()
{
	auto pair_hash_lambda = [](const auto& p)->int
	{
		int seed = 0;
		seed ^= hash<decltype(p.first)>()(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= hash<decltype(p.second)>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	};
	auto pair_eq = [](const auto& p1,const auto& p2)->bool
	{
		return p1.first == p2.first && p1.second == p2.second;
	};
	unordered_map<pair<int, int>, int, decltype(pair_hash_lambda), decltype(pair_eq)>hash_map;
	hash_map[{1, 3}] = 1;
	hash_map[{3, 5}] = 2;
	hash_map[{4, 2}] = 3;
	hash_map[{3, 1}] = 5;
	hash_map[{1, 3}] = 4;
	hash_map[{2, 6}] = 6;
	for (auto& x : hash_map)
	{
		cout << "{" << x.first.first << "," << x.first.second << "}" << "->" << x.second << endl;
	}
	return;
}
int main()
{
	pair_as_map_key();
	putchar('\n');
	pair_as_map_key_lambda();
	putchar('\n');
	pair_as_hashmap();
	putchar('\n');
	pair_as_hashmap_lambda();
	return 0;
}
/*map
{1, 1}->10
{1, 2}->10
{3, 3}->20
{3, 4}->20
{5, 1}->20
*/
/*hash
{3,1}->5
{1,3}->4
{3,5}->2
{2,6}->6
{4,2}->3
*/