// Fill out your copyright notice in the Description page of Project Settings.


#include "LabTools/LabTool.h"


FLabTools* ALabTool::GetToolById(int32 ToolId)
{
	auto Result = ToolsArray.FindByPredicate([ToolId](FLabTools Tool)
	{
		return ToolId == Tool.ToolId;
	});
	return Result;
}
