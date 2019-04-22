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
	PlayerTurn,AITurn // состо€ни€ - ход игрока, ход »»
};
USTRUCT(Blueprintable)
	struct FMovement    //структура, представл€юща€ собой ход
	{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveStruct")
		int32 index;   // номер сокета дл€ хода
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveStruct")
		int32 score;   //вес хода
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
	ASocket* OriginalBoard; //массив сокетов, представл€ющих поле
	std::vector<int32> EmptySlots(TArray<ASocket*> board); //функци€, определ€юща€ индексы незан€тых полей
	UFUNCTION(BlueprintCallable)
	bool winning(TArray<ASocket*> board, FString Player);  //проверка на победу Player
	UFUNCTION(BlueprintCallable)
	FMovement MiniMax(TArray<ASocket*> NewBoard, FString Player); //непосредственно функци€ алгоритма MiniMax, котора€ возвращает структуру с индексом лучшего хода дл€ фишки Player
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
