#include <iostream>
#include "Log.h"

//std::vector<LogEntry> Log::LogEntries;
//
//void Log::LogMessage(LogType Type, const std::string& Message)
//{
//	LogEntry Entry;
//	Entry.Type = Type;
//	Entry.Message = Message;
//	LogEntries.push_back(Entry);
//	PrintLog(Entry);
//}
//
//void Log::Separartor()
//{
//	std::cout << "----------------" << std::endl;
//}
//
//void Log::NewLine()
//{
//	std::cout << std::endl;
//}
// 
//
//void Log::PrintLog(LogEntry& Entry)
//{
//	std::string color;
//	switch (Entry.Type)
//	{
//	case LOG_INFO:
//		color = "\x1B[32m";
//		break;
//	case LOG_WARNING:
//		color = "\x1B[33m";
//		break;
//	case LOG_ERROR:
//		color = "\x1B[91m";
//		break;
//	case LOG_DEFAULT:
//	default:
//		color = "\x1B[37m";
//		break;
//	} 
//
//	std::cout << color << Entry.Message << "\033[0m" << std::endl; 
//
//}
//
//
