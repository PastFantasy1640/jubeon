#pragma once

#ifndef WG_SYSTEMS_INIFILEREADER_HPP
#define WG_SYSTEMS_INIFILEREADER_HPP

#include <string>
#include <fstream>
#include <vector>

namespace wg {
	namespace systems {
		class INIFileReader {
		public:

			/// <summary>�R���X�g���N�^</summary>
			INIFileReader(void);

			/// <summary>�R�s�[�R���X�g���N�^</summary>
			INIFileReader(const INIFileReader & copy);

			/// <summary>�f�X�g���N�^</summary>
			virtual ~INIFileReader(void);

			/// <summary>ini�t�@�C�������[�h����</summary>
			/// <param name='filename'>�t�@�C����</param>
			/// <returns>����:true   ���s:false</returns>
			bool load(const std::string filename);

			/// <summary>ini�t�@�C���̒l���擾����</summary>
			/// <param name='section'>�Z�N�V����</param>
			/// <param name='key'>�L�[</param>
			/// <param name='def_str'>�f�t�H���g����</param>
			/// <param name='is_existed'>�w�肳�ꂽ�L�[�����݂��������i�[����</param>
			/// <returns>�w�肳�ꂽ�L�[�̕������Ԃ�</returns>
			std::string get(const std::string section, const std::string key, const std::string def_str = "", bool * is_existed = nullptr) const;

			/// <summary>ini�t�@�C���̒l��V��������������</summary>
			/// <param name='section'>�Z�N�V����</param>
			/// <param name='key'>�L�[</param>
			/// <param name='value'>�������ޒl</param>
			bool update(const std::string section, const std::string key, std::string new_str);

			/// <summary>�ێ����Ă���f�[�^�̃N���A</summary>
			void clear(void);

			/// <summary>ini�t�@�C�����ēǂݍ��݂���</summary>
			bool flush(void);

		private:

			struct INIFileReaderElements {
				std::string section;
				std::string key;
				std::string value;
			};

			std::vector<INIFileReaderElements> * data;

			std::fstream * file_stream;

			std::string filename;

			bool is_load_successfully;

			INIFileReaderElements _Psc(const std::string s);
			bool _ISp(const std::string s) const;
		};
	};
};


#endif	//eof WG_SYSTEMS_INIFILEREADER_HPP
