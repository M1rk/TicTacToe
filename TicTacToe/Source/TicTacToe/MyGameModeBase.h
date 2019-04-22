// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Socket.h"
#include <vector>
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

UENUM(BlueprintType)
enum class ETurn : uint8
{
	PlayerTurn,AITurn // ��������� - ��� ������, ��� ��
};
USTRUCT(Blueprintable)
	struct FMovement    //���������, �������������� ����� ���
	{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveStruct")
		int32 index;   // ����� ������ ��� ����
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveStruct")
		int32 score;   //��� ����
	};
UCLASS()
class TICTACTOE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
	ETurn TurnState;
	AMyGameModeBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
	FString PlayerMark;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
	FString AIMark;
	UPROPERTY()
	ASocket* OriginalBoard; //������ �������, �������������� ����
	std::vector<int32> EmptySlots(TArray<ASocket*> board); //�������, ������������ ������� ��������� �����
	UFUNCTION(BlueprintCallable)
	bool winning(TArray<ASocket*> board, FString Player);  //�������� �� ������ Player
	UFUNCTION(BlueprintCallable)
	FMovement MiniMax(TArray<ASocket*> NewBoard, FString Player); //��������������� ������� ��������� MiniMax, ������� ���������� ��������� � �������� ������� ���� ��� ����� Player
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
