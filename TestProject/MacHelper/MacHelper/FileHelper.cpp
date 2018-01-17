//
//  FileHelper.cpp
//  MacHelper
//
//  Created by gongxun on 15/8/4.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "FileHelper.h"
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::archive::iterators;

string FileHelper::gStartPath = "";

string FileHelper::gProjectName = "MacHelper";

FileHelper::FileHelper()
{
    
}

FileHelper::~FileHelper()
{
    
}

const char * say_what(bool b) { return b ? "true" : "false"; }

void FileHelper::showFileInfo(const string &file)
{
    fs::path p(file);
    
    cout  <<  "\ncomposed path:\n";
    cout  <<  "  cout << -------------: " << p << "\n";
    cout  <<  "  make_preferred()----------: " << fs::path(p).make_preferred() << "\n";
    
    cout << "\nelements:\n";
    
    for (fs::path::iterator it(p.begin()), it_end(p.end()); it != it_end; ++it)
        cout << "  " << *it << '\n';
    
    cout  <<  "\nobservers, native format:" << endl;
# ifdef BOOST_POSIX_API
    cout  <<  "  native()-------------: " << p.native() << endl;
    cout  <<  "  c_str()--------------: " << p.c_str() << endl;
# else  // BOOST_WINDOWS_API
    wcout << L"  native()-------------: " << p.native() << endl;
    wcout << L"  c_str()--------------: " << p.c_str() << endl;
# endif
    cout  <<  "  string()-------------: " << p.string() << endl;
    wcout << L"  wstring()------------: " << p.wstring() << endl;
    
    cout  <<  "\nobservers, generic format:\n";
    cout  <<  "  generic_string()-----: " << p.generic_string() << endl;
    wcout << L"  generic_wstring()----: " << p.generic_wstring() << endl;
    
    cout  <<  "\ndecomposition:\n";
    cout  <<  "  root_name()----------: " << p.root_name() << '\n';
    cout  <<  "  root_directory()-----: " << p.root_directory() << '\n';
    cout  <<  "  root_path()----------: " << p.root_path() << '\n';
    cout  <<  "  relative_path()------: " << p.relative_path() << '\n';
    cout  <<  "  parent_path()--------: " << p.parent_path() << '\n';
    cout  <<  "  filename()-----------: " << p.filename() << '\n';
    cout  <<  "  stem()---------------: " << p.stem() << '\n';
    cout  <<  "  extension()----------: " << p.extension() << '\n';
    
    cout  <<  "\nquery:\n";
    cout  <<  "  empty()--------------: " << say_what(p.empty()) << '\n';
    cout  <<  "  is_absolute()--------: " << say_what(p.is_absolute()) << '\n';
    cout  <<  "  has_root_name()------: " << say_what(p.has_root_name()) << '\n';
    cout  <<  "  has_root_directory()-: " << say_what(p.has_root_directory()) << '\n';
    cout  <<  "  has_root_path()------: " << say_what(p.has_root_path()) << '\n';
    cout  <<  "  has_relative_path()--: " << say_what(p.has_relative_path()) << '\n';
    cout  <<  "  has_parent_path()----: " << say_what(p.has_parent_path()) << '\n';
    cout  <<  "  has_filename()-------: " << say_what(p.has_filename()) << '\n';
    cout  <<  "  has_stem()-----------: " << say_what(p.has_stem()) << '\n';
    cout  <<  "  has_extension()------: " << say_what(p.has_extension()) << '\n';
}

void FileHelper::testOutFile()
{
    fs::path p("projectHall.manifest");
    
    fs::ifstream ifile;
    ifile.open(p);
    
    fs::ofstream ofile;
    ofile.open("projectHall.temp");
    
    string s;
    while (getline(ifile, s))
    {
        ofile<<s<<endl;
    }
}

string FileHelper::getKeyOrValue(const string &key, const string &value)
{
    ostringstream oss;
    string result;
    oss<<'"';
    oss<<key;
    oss<<'"';
    oss<<" : ";
    oss<<'"';
    oss<<value;
    oss<<'"';
    result = oss.str();
    return result;
}

void FileHelper::copyFile(const string &fromFile, const string &toFile)
{
    auto parent_path = fs::path(toFile).parent_path();
    if (!fs::exists(parent_path))
    {
        fs::create_directories(parent_path);
    }
    fs::copy_file(fromFile, toFile, fs::copy_option::overwrite_if_exists);
}

vector<string> FileHelper::getDirectoryOnlyFile(const string &path)
{
    vector<string> result;
    
    for (fs::directory_entry& x : fs::directory_iterator(path))
    {
        if (!fs::is_directory(x))
        {
            string temp = x.path().string();
            result.push_back(temp);
        }
    }
    
    return result;
}

vector<string> FileHelper::getDirectoryFile(const string &path)
{
    vector<string> files;
    getFileForDirectory(path, files);
//    for (auto &it : files)
//    {
//        fs::path p(it);
//        cout<<"fileName:"<<p.filename()<<" fileExtension:"<<p.extension()<<endl;
//    }
    return files;
}

void FileHelper::getFileForDirectory(const string &path, vector<string> &fileNames)
{
    try
    {
        if (fs::exists(path))
        {
            if (fs::is_regular_file(path))
            {
                if (fs::path(path).extension().string() != ".DS_Store"){
                    fileNames.push_back(path);
                }
            }
            else if (fs::is_directory(path))
            {
                for (fs::directory_entry& x : fs::directory_iterator(path))
                {
                    getFileForDirectory(x.path().string(), fileNames);
                }
            }
            else
                cout << path << " exists, but is not a regular file or directory\n";
        }
        else
            cout << path << " does not exist\n";
    }
    
    catch (const fs::filesystem_error& ex)
    {
        cout << ex.what() << '\n';
    }
}

vector<string> FileHelper::getDirectory(const string &path)
{
    vector<string> result;
    
    for (fs::directory_entry& x : fs::directory_iterator(path))
    {
        if (fs::is_directory(x))
        {
            string temp = x.path().string();
            result.push_back(temp);
        }
    }
    
    return result;
}

vector<string> FileHelper::getDirectorys(const string &path)
{
    vector<string> result;
    
    boost::filesystem::recursive_directory_iterator end; //设置遍历结束标志，用recursive_directory_iterator即可循环的遍历目录
    boost::system::error_code ec;
    for (boost::filesystem::recursive_directory_iterator pos(path); pos != end; ++pos)
    {
        //过滤掉目录和子目录为空的情况
        if(fs::is_directory(*pos))
        {
            result.push_back((*pos).path().string());
        }
    }
    
    return result;
}

string FileHelper::getFileName(const string &path)
{
    fs::path p(path);
    return p.filename().string();
}

int FileHelper::removeFile(const string &path)
{
    return fs::remove_all(path);
}

//void getJSONFile(const string &fileName, boost::property_tree::ptree &outPtree)
//{
//    fstream inFile;
//    inFile.open(fileName.c_str());
//    
//    stringstream ss;
//    ss<<inFile.rdbuf();
//    try
//    {
//        read_json(ss, outPtree);
//    }
//    catch (boost::property_tree::ptree_error & e)
//    {
//        throw "不是json文件";
//    }
//}


bool FileHelper::Base64Encode(const string & inPut, string &outPut)
{
    typedef base64_from_binary<transform_width<string::const_iterator,6,8>> Base64EncodeIter;
    
    stringstream  result;
    copy(Base64EncodeIter(inPut.begin()),
         Base64EncodeIter(inPut.end()),
         ostream_iterator<char>(result));
    
    size_t Num = (3 - inPut.length() % 3) % 3;
    for (size_t i = 0; i < Num; i++)
    {
        result.put('=');
    }
    outPut = result.str();
    return outPut.empty() == false;
}

bool FileHelper::Base64Decode(const string & inPut, string &outPut)
{
    typedef transform_width<binary_from_base64<string::const_iterator>,8,6> Base64DecodeIter;
    
    stringstream result;
    try
    {
        copy(Base64DecodeIter(inPut.begin()),
             Base64DecodeIter(inPut.end()),
             ostream_iterator<char>(result));
    }
    catch (...)
    {
        return false;
    }
    outPut = result.str();
    return outPut.empty() == false;
}

void FileHelper::copyDirectory(const string &source, const string &dir)
{
    boost::filesystem::recursive_directory_iterator end; //设置遍历结束标志，用recursive_directory_iterator即可循环的遍历目录
    boost::system::error_code ec;
    for (boost::filesystem::recursive_directory_iterator pos(source); pos != end; ++pos)
    {
        //过滤掉目录和子目录为空的情况
        if(boost::filesystem::is_directory(*pos))
            continue;
        std::string strAppPath = boost::filesystem::path(*pos).string();
        std::string strRestorePath;
        //replace_first_copy在algorithm/string头文件中，在strAppPath中查找strSourceDir字符串，找到则用strDestDir替换，替换后的字符串保存在一个输出迭代器中
        boost::replace_first_copy(std::back_inserter(strRestorePath), strAppPath, source, dir);
        if(!boost::filesystem::exists(boost::filesystem::path(strRestorePath).parent_path()))
        {
            boost::filesystem::create_directories(boost::filesystem::path(strRestorePath).parent_path(), ec);
        }
        boost::filesystem::copy_file(strAppPath, strRestorePath, boost::filesystem::copy_option::overwrite_if_exists, ec);
    }
}

void FileHelper::createDir(const string &dir)
{
    if (!boost::filesystem::is_directory(dir))
    {
        boost::filesystem::create_directory(dir);
    }
}

























