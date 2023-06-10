#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "picojson.h"

std::string INPUT_DIR="./library/";
std::string OUTPUT_DIR="~/.vscode/";

//それぞれのコードをjson形式に変換
picojson::object snippet_create(std::string name,std::string path){

    std::ifstream ifs(path);
    std::string str;
    std::vector<std::string> strs;

    if(ifs.fail()){
        std::cerr<<"Failed to open file"<<std::endl;
        std::exit(0);
    }
    while(getline(ifs,str)){
        strs.push_back(str);
    }
    picojson::object snippet_object;
    picojson::array arr;
    for(auto s:strs){
        arr.emplace_back(picojson::value(s));
    }
    snippet_object["body"]=picojson::value(arr);
    snippet_object["prefix"]=picojson::value(name);

    return snippet_object;
}

int main(){

    picojson::object snippets_object;

    for(const auto & file : std::filesystem::directory_iterator(INPUT_DIR)){
        std::string path=file.path(),filename=file.path().filename();
        std::string name=filename.substr(0,filename.length()-4);
        picojson::object snippet=snippet_create(name,path);
        std::cerr<<name<<std::endl;
        snippets_object[name]=picojson::value(snippet);
    }

    std::cerr<<"output > ./cpp.code-snippets"<<std::endl;
    std::ofstream output_file("./cpp.code-snippets");

    if(!output_file){
        std::cerr<<"Failed to open file"<<std::endl;
        std::exit(1);
    }

    output_file<<picojson::value(snippets_object).serialize()<<std::endl;
    output_file.close();

    std::cout<<"Success! Snippets Generated!"<<std::endl;

    return 0;
}
/*
コードをjsonに変換したものをさらにタイトルつけてjsonオブジェクトにするんだね
bodyは一行ごとに配列に入れてね？


参照記事
https://github.com/sk4rdz/competitive-cpp/blob/master/snippet_generator.py
https://qiita.com/282Haniwa/items/82828c6a566e3e7e047d#snippet%E3%81%A8%E3%81%AF
https://www.delftstack.com/ja/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/
https://phst.hateblo.jp/entry/2017/07/26/144837
https://github.com/kazuho/picojson
https://akira206.hatenablog.com/entry/2016/06/26/204801
https://qiita.com/ayase/items/58c9e63e96857d83ebd9
https://www.delftstack.com/ja/howto/cpp/how-to-read-a-file-line-by-line-cpp/
https://qiita.com/ShinyaOkazawa/items/bc86a876a16646c0002a
*/