// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"


AMyGameModeBase::AMyGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

std::vector<int32> AMyGameModeBase::EmptySlots(TArray<ASocket*> board)
{
	std::vector<int32> EmptySocketsIndexes;
	
	for(int32 i = 0;i<9; i++) //проходим по всем сокетам поля, находим пустые, помещаем в EmptySocketIndexes
	{
		
		if(board[i]->State == ESocketState::Empty)
		{
			EmptySocketsIndexes.push_back(i); 
		}
	}
	return EmptySocketsIndexes;
}

bool AMyGameModeBase::winning(TArray<ASocket*> board, FString Player)
{
	if (Player == "X")
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i * 3]->State == ESocketState::XMark && board[i * 3 + 1]->State == ESocketState::XMark && board[i * 3 + 2]->State == ESocketState::XMark) //гормзонталь
			{
				return  true; 
			}
			
			else if (board[i]->State == ESocketState::XMark && board[i + 3]->State == ESocketState::XMark && board[i + 6]->State == ESocketState::XMark) //вертикаль
			{
				return true;
			}
			else if ((board[2]->State == ESocketState::XMark && board[4]->State == ESocketState::XMark  && board[6]->State==ESocketState::XMark) ||  //диагонали
				(board[0]->State == ESocketState::XMark && board[4]->State == ESocketState::XMark  && board[8]->State == ESocketState::XMark))
			{
				return true; 
			}
		}
			return false;
	}

	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i * 3]->State == ESocketState::OMark && board[i * 3 + 1]->State == ESocketState::OMark && board[i * 3 + 2]->State == ESocketState::OMark) //гормзонталь
			{
				return  true;
			}

			else if (board[i]->State == ESocketState::OMark && board[i + 3]->State == ESocketState::OMark && board[i + 6]->State == ESocketState::OMark) //вертикаль
			{
				return true;
			}
			else if ((board[2]->State == ESocketState::OMark && board[4]->State == ESocketState::OMark  && board[6]->State == ESocketState::OMark) ||  //диагонали
				(board[0]->State == ESocketState::OMark && board[4]->State == ESocketState::OMark  && board[8]->State == ESocketState::OMark))
			{
				return true;
			}
		}
			return false;
	}
}

FMovement AMyGameModeBase::MiniMax(TArray<ASocket*> NewBoard, FString Player)
{
	std::vector<int32> AvailSlots = EmptySlots(NewBoard); //массив доступных для хода индексов
	//проверяем на конечные состояния победы/ничьей и возвращаем ход с соответствующим весом
		if(winning(NewBoard,"X"))
		{
			FMovement move;
			move.index = 0;
			move.score = -10;
			return move;
		}
		else if (winning(NewBoard, "0"))
		{
			FMovement move;
			move.index = 0;
			move.score = 10;
			return move;
		}
		else if (AvailSlots.empty())
		{
			FMovement move;
			move.index = 0;
			move.score = 0;
			return move;
		}
	
	

	std::vector<FMovement> Moves;                 //массив ходов с их весами и индексами
	for(int32 i = 0; i<AvailSlots.size(); i++)    //для каждой пустой клетки создаём структуру хода move с индексом выбранного слота
	{
		FMovement move;
		move.index = NewBoard[AvailSlots[i]]->index; 
		//делаем ход подходящей фишкой
		if(Player == "X")
		{
			NewBoard[AvailSlots[i]]->State = ESocketState::XMark; 
		}
		else if(Player == "0")
		{
			NewBoard[AvailSlots[i]]->State = ESocketState::OMark;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("incorrect player input"));
		}
		//рекурсивно запускаем МиниМакс функцию для вновь полученной конфигурации поля, сменив фишку на противоположную,имитируя ход противника
		if(Player == "0")
		{
			FMovement result = MiniMax(NewBoard, "X");
			move.score = result.score;
		}
		else
		{
			FMovement result = MiniMax(NewBoard, "0");

			move.score = result.score;
		}
		NewBoard[AvailSlots[i]]->State = ESocketState::Empty; //возвращаем поле в исходное состояние
		
		Moves.push_back(move);   //добавляем полученный ход в массив Moves
	}
	
	
	int32 BestMovementIndex; //индекс лучшего хода
	//в завивимости от фишки определяем индекс лучшего хода
	if (Player == "0")
	{
		int32 BestScore = -10000;
		for (int32 i = 0; i < Moves.size(); i++)
		{
			if (Moves[i].score > BestScore)
			{
				BestScore = Moves[i].score;
				BestMovementIndex = i;
			}
		}
		
	}
	else
	{
		int32 BestScore = 10000;
		for(int32 i = 0;i< Moves.size();i++)
		{
			if(Moves[i].score < BestScore)
			{
				BestScore = Moves[i].score;
				BestMovementIndex = i;
			}
		}
		
	}
	
	std::vector<int32> array; //вспомогательный массив, в который заносим ходы, которые по весу равны лучшему
	if(Moves.size()>0)
	{
		for (int32 i = 0; i < Moves.size(); i++)
		{
			if (Moves[i].score == Moves[BestMovementIndex].score)
			{
				array.push_back(i);
			}
		}
		int32 randomindex = FMath::RandRange(0, (int32)array.size() - 1); //среди лучших ходов выбираем случайный
	
	BestMovementIndex = array[randomindex];
	
	}
	
	return Moves[BestMovementIndex]; //возвращаем лучший ход
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyGameModeBase::Tick(float DeltaTime)
{
	
}
